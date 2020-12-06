#pragma once

#include "shapes/shape.h"
#include "light/point_light.h"
#include "intersection/intersection.h"
#include "intersection/hit.h"
#include "light/background.h"
#include <vector>
#include <memory>

class World {

public:
    std::vector<std::shared_ptr<Shape>> objects;
    std::vector<PointLight> lights;
    std::shared_ptr<Background> background;

    World();
    static World example_world();

    std::vector<Intersection> intersect(const Ray& ray) const;

    bool is_shadowed(const Tuple& point, const PointLight &light) const;

    Color shade_hit(const Hit& hit, int remaining) const;

    Color color_at(const Ray& ray, int remaining) const;
};
