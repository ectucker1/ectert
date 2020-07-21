#include "world.h"

#include "math/transform.h"

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

Color World::shade_hit(const Hit &hit) const {
    Color total = Color();
    for (PointLight light : lights) {
        bool shadowed = is_shadowed(hit.over_point, light);
        total = total + hit.object->material.lighting(hit.object, light, hit.point, hit.eyev, hit.normalv, shadowed);
    }
    return total;
}

Color World::color_at(const Ray &ray) const {
    std::vector<Intersection> xs = intersect(ray);
    Intersection x = hit(xs);
    if (x == Intersection::NIL) {
        return Color(0, 0, 0);
    }

    Hit data = Hit(x, ray);
    return shade_hit(data);
}
