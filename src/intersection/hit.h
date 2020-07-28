#pragma once

#include "math/tuple.h"
#include "shapes/shape.h"

class Hit {

public:
    float t;
    const std::shared_ptr<const Shape> object;

    Tuple point = Tuple::point(0, 0, 0);
    Tuple eyev = Tuple::vector(0, 0, 0);
    Tuple normalv = Tuple::vector(0, 0, 0);
    Tuple reflectv = Tuple::vector(0, 0, 0);

    float n1;
    float n2;

    bool inside = false;

    Tuple over_point = Tuple::point(0, 0, 0);
    Tuple under_point = Tuple::point(0, 0, 0);

    Hit(const Intersection& intersection, const Ray& ray,
            const std::vector<Intersection>& xs = std::vector<Intersection>());

};
