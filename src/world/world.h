#pragma once

#include "intersection/sphere.h"
#include "light/point_light.h"
#include "intersection/intersection.h"
#include "intersection/hit.h"
#include <vector>

class World {

public:
    std::vector<Sphere> objects;
    PointLight light;

    World();
    static World example_world();

    std::vector<Intersection> intersect(const Ray& ray) const;

    Color shade_hit(const Hit& hit) const;

    Color color_at(const Ray& ray) const;

};
