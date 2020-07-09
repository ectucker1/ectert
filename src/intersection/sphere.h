#pragma once

class Intersection;

#include "ray.h"
#include "intersection.h"
#include "light/material.h"
#include <vector>

class Sphere {

public:
    Material material;

    Sphere();
    Sphere(const Matrix& transform);

    Matrix transform();
    void transform(const Matrix& trans);

    Matrix inverse();

    std::vector<Intersection> intersect(Ray ray) const;

    Tuple normal_at(const Tuple point) const;

    bool operator ==(const Sphere& other) const;

private:
    Matrix _transform;
    Matrix _inverse;

};
