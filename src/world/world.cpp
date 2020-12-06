#include "world.h"

#include "math/transform.h"
#include "light/scatter.h"
#include "shapes/sphere.h"
#include "light/gradient_background.h"

World::World() {
    objects = std::vector<std::shared_ptr<Shape>>();
    background = std::make_shared<GradientBackground>(Color(), Color());
}

World World::example_world() {
    World world = World();

    auto s1 = std::make_shared<Sphere>();
    //s1->material.color = Color(0.8, 1.0, 0.6);
    //s1->material.diffuse = 0.7;
    //s1->material.specular = 0.2;
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

Color World::shade_hit(const Hit &hit, int remaining) const {
    // If there are no scatters remaining
    if (remaining <= 0) {
        return Color(0, 0, 0);
    }

    std::shared_ptr<Material> mat = hit.object->material;
    Scatter scatter = mat->scatter(hit);
    Color emitted = mat->emitted(hit);

    // If the light scattered
    if (!scatter.absorbed) {
        return emitted + scatter.attenuation * color_at(scatter.scattered, remaining - 1);
    } else {
        // Return only the emitted part if light was absorbed
        return emitted;
    }
}

Color World::color_at(const Ray &ray, int remaining) const {
    std::vector<Intersection> xs = intersect(ray);
    Intersection x = hit(xs);
    if (x == Intersection::NIL) {
        return background->sample_background(ray);
    }

    Hit data = Hit(x, ray, xs);
    return shade_hit(data, remaining);
}
