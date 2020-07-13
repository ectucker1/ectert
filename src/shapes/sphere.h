#pragma once

class Intersection;

#include "intersection/ray.h"
#include "intersection/intersection.h"
#include "light/material.h"
#include <vector>

class Sphere : public Shape {

public:
    Sphere();
    Sphere(const Matrix& transform);

    bool operator ==(const Sphere& other) const;

private:
    virtual std::vector<Intersection> local_intersect(const Ray& local_ray) const;
    virtual Tuple local_normal_at(const Tuple& local_point) const;

};
