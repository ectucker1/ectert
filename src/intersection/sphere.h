#pragma once

class Intersection;

#include "ray.h"
#include "intersection.h"
#include <vector>

class Sphere {

public:
    Matrix transform;

    Sphere();
    Sphere(const Matrix& transform);

    std::vector<Intersection> intersect(Ray ray);

    bool operator ==(const Sphere& other) const;

};
