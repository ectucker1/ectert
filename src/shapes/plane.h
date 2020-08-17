#pragma once

#include "shape.h"

class Plane : public Shape {

public:
    Plane();
    Plane(const Matrix& transform);

    Bounds bounds() const override;

private:
    std::vector<Intersection> local_intersect(const Ray& local_ray) const override;
    Tuple local_normal_at(const Tuple& local_point, const Intersection& intersection) const override;

};
