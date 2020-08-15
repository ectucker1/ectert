#pragma once

#include "shape.h"

class Sphere : public Shape {

public:
    Sphere();
    Sphere(const Matrix& transform);

    bool operator ==(const Sphere& other) const;

    Bounds bounds() const override;

private:
    std::vector<Intersection> local_intersect(const Ray& local_ray) const override;
    Tuple local_normal_at(const Tuple& local_point) const override;

};
