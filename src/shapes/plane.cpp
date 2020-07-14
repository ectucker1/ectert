#include "plane.h"
#include "math/float_util.h"

Plane::Plane() : Shape() {}

Plane::Plane(const Matrix &transform) : Shape(transform) {}

std::vector<Intersection> Plane::local_intersect(const Ray &local_ray) const {
    std::vector<Intersection> results = std::vector<Intersection>();

    if (!float_equal(local_ray.direction.y, 0)) {
        results.emplace_back(-local_ray.origin.y / local_ray.direction.y, shared_from_this());
    }

    return results;
}

Tuple Plane::local_normal_at(const Tuple &local_point) const {
    return Tuple::vector(0, 1, 0);
}
