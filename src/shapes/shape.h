#pragma once

class Intersection;

#include "intersection/ray.h"
#include "intersection/intersection.h"
#include "light/material.h"
#include <vector>

class Shape {

public:
    Material material;

    Shape();
    Shape(const Matrix& transform);

    Matrix transform() const;
    void transform(const Matrix& trans);

    Matrix inverse() const;

    std::vector<Intersection> intersect(const Ray& ray) const;

    Tuple normal_at(const Tuple& point) const;

private:
    Matrix _transform;
    Matrix _inverse;

    virtual std::vector<Intersection> local_intersect(const Ray& local_ray) const = 0;
    virtual Tuple local_normal_at(const Tuple& local_point) const = 0;

};
