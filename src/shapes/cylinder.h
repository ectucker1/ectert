#pragma once

#include "shape.h"
#include <cmath>

class Cylinder : public Shape {

public:
    float minimum = -INFINITY;
    float maximum = INFINITY;

    bool closed = false;

    Cylinder();
    Cylinder(const Matrix& transform);

    Bounds bounds() const override;

private:
    std::vector<Intersection> local_intersect(const Ray& local_ray) const override;
    bool check_caps(const Ray& local_ray, const float t) const;
    void intersect_caps(const Ray& local_ray, std::vector<Intersection>& xs) const;
    Tuple local_normal_at(const Tuple& local_point) const override;

};
