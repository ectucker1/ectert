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

    bool inside = false;

    Tuple over_point = Tuple::point(0, 0, 0);

    Hit(const Intersection& intersection, const Ray& ray);

};
