#pragma once

#include "shapes/sphere.h"
#include "light/point_light.h"
#include "intersection/intersection.h"
#include "intersection/hit.h"
#include <vector>

class World {

public:
    std::vector<Sphere> objects;
    std::vector<PointLight> lights;

    World();
    static World example_world();

    std::vector<Intersection> intersect(const Ray& ray) const;

    bool is_shadowed(const Tuple& point, const PointLight &light) const;

    Color shade_hit(const Hit& hit) const;

    Color color_at(const Ray& ray) const;

};
