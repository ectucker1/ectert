#include "world.h"

#include "math/transform.h"

World::World() : light(PointLight::NIL), objects(std::vector<Sphere>()) {}

World World::example_world() {
    World world = World();

    PointLight light = PointLight(Tuple::point(-10, 10, -10), Color(1, 1, 1));
    world.light = light;

    Sphere s1 = Sphere();
    s1.material.color = Color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;
    world.objects.push_back(s1);

    Sphere s2 = Sphere(scaling(0.5, 0.5, 0.5));
    world.objects.push_back(s2);

    return world;
}

std::vector<Intersection> World::intersect(const Ray& ray) const {
    std::vector<Intersection> worldXS = std::vector<Intersection>();
    for (const Sphere& object : objects) {
        std::vector<Intersection> objectXS = object.intersect(ray);
        worldXS.insert(worldXS.begin(), objectXS.begin(), objectXS.end());
    }
    return sort_intersections(worldXS);
}

bool World::is_shadowed(const Tuple &point) const {
    Tuple vec = light.position - point;

    float dist = vec.magnitude_sq();
    Tuple dir = vec.normalized();

    Ray ray = Ray(point, dir);
    std::vector<Intersection> xs = intersect(ray);
    Intersection x = hit(xs);

    return !(x == Intersection::NIL) && x.t * x.t < dist;
}

Color World::shade_hit(const Hit &hit) const {
    // TODO: Multiple light sources

    bool shadowed = is_shadowed(hit.over_point);

    return hit.object->material.lighting(light, hit.point, hit.eyev, hit.normalv, shadowed);
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
