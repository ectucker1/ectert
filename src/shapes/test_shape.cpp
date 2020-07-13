#include "test_shape.h"

TestShape::TestShape() : Shape() {}

TestShape::TestShape(const Matrix &transform) : Shape(transform) {}

std::vector<Intersection> TestShape::local_intersect(const Ray &local_ray) const {
    std::vector<Intersection> xs = std::vector<Intersection>();
    xs.emplace_back(0.0, this);
    xs.emplace_back(local_ray.direction.magnitude(), this);
    return xs;
}

Tuple TestShape::local_normal_at(const Tuple &local_point) const {
    return Tuple::vector(local_point.x, local_point.y, local_point.z);
}
