#include "world.h"

#include "math/transform.h"
#include <cmath>

World::World() : lights(std::vector<PointLight>()), objects(std::vector<std::shared_ptr<Shape>>()) {}

World World::example_world() {
    World world = World();

    PointLight light = PointLight(Tuple::point(-10, 10, -10), Color(1, 1, 1));
    world.lights.push_back(light);

    auto s1 = std::make_shared<Sphere>();
    s1->material.color = Color(0.8, 1.0, 0.6);
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;
    world.objects.push_back(s1);

    auto s2 = std::make_shared<Sphere>(scaling(0.5, 0.5, 0.5));
    world.objects.push_back(s2);

    return world;
}

std::vector<Intersection> World::intersect(const Ray& ray) const {
    std::vector<Intersection> worldXS = std::vector<Intersection>();
    for (const std::shared_ptr<Shape> object : objects) {
        std::vector<Intersection> objectXS = object->intersect(ray);
        worldXS.insert(worldXS.begin(), objectXS.begin(), objectXS.end());
    }
    return sort_intersections(worldXS);
}

bool World::is_shadowed(const Tuple &point, const PointLight &light) const {
    Tuple vec = light.position - point;

    float dist = vec.magnitude_sq();
    Tuple dir = vec.normalized();

    Ray ray = Ray(point, dir);
    std::vector<Intersection> xs = intersect(ray);
    Intersection x = hit(xs);

    return !(x == Intersection::NIL) && x.t * x.t < dist;
}

Color World::shade_hit(const Hit &hit, int remaining) const {
    Color total = Color();
    for (PointLight light : lights) {
        bool shadowed = is_shadowed(hit.over_point, light);
        Color surface = hit.object->material.lighting(hit.object, light, hit.point, hit.eyev, hit.normalv, shadowed);
        Color reflected = reflected_color(hit, remaining);
        Color refracted = refracted_color(hit, remaining);
        total = total + surface + reflected + refracted;
    }
    return total;
}

Color World::color_at(const Ray &ray, int remaining) const {
    std::vector<Intersection> xs = intersect(ray);
    Intersection x = hit(xs);
    if (x == Intersection::NIL) {
        return Color(0, 0, 0);
    }

    Hit data = Hit(x, ray, xs);
    return shade_hit(data, remaining);
}

Color World::reflected_color(const Hit& hit, int remaining) const {
    if (remaining < 1 || hit.object->material.reflectivity == 0) {
        return Color(0, 0, 0);
    }

    remaining--;

    Ray reflect_ray = Ray(hit.over_point, hit.reflectv);
    Color color = color_at(reflect_ray, remaining);

    return color * hit.object->material.reflectivity;
}

Color World::refracted_color(const Hit& hit, int remaining) const {
    // Default to black if object is not transparent or no recursive calls remaining
    if (remaining < 1 || hit.object->material.alpha >= 1.0) {
        return Color(0, 0, 0);
    }

    // Ratio of refractive indices
    float n_ratio = hit.n1 / hit.n2;
    // Dot product = cosine for normal vectors
    float cos_i = hit.eyev.dot(hit.normalv);
    // Trig identity stuff
    float sin2_t = n_ratio * n_ratio * (1 - cos_i * cos_i);

    // Total internal refraction
    if (sin2_t > 1) {
        return Color(0, 0, 0);
    }

    float cos_t = sqrtf(1 - sin2_t);
    // Direction of refracted ray
    Tuple direction = hit.normalv * (n_ratio * cos_i - cos_t) - hit.eyev * n_ratio;

    Ray ray = Ray(hit.under_point, direction);

    return color_at(ray, remaining - 1) * (1 - hit.object->material.alpha);
}
