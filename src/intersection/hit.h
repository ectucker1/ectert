#pragma once

#include "math/tuple.h"
#include "sphere.h"

class Hit {

public:
    float t;
    const Sphere* object = nullptr;

    Tuple point = Tuple::point(0, 0, 0);
    Tuple eyev = Tuple::vector(0, 0, 0);
    Tuple normalv = Tuple::vector(0, 0, 0);

    bool inside = false;

    Tuple over_point = Tuple::point(0, 0, 0);

    Hit(const Intersection& intersection, const Ray& ray);

};
