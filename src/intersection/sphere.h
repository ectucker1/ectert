#pragma once

class Intersection;

#include "ray.h"
#include "intersection.h"
#include "light/material.h"
#include <vector>

class Sphere {

public:
    Matrix transform;

    Material material;

    Sphere();
    Sphere(const Matrix& transform);

    std::vector<Intersection> intersect(Ray ray);

    Tuple normal_at(const Tuple point) const;

    bool operator ==(const Sphere& other) const;

};
