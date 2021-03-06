#include "plane.h"
#include "math/bounds.h"
#include "math/float_util.h"
#include <cmath>

Plane::Plane() : Shape() {}

Plane::Plane(const Matrix &transform) : Shape(transform) {}

std::vector<Intersection> Plane::local_intersect(const Ray &local_ray) const {
    std::vector<Intersection> results = std::vector<Intersection>();

    if (!float_equal(local_ray.direction.y, 0)) {
        results.emplace_back(-local_ray.origin.y / local_ray.direction.y, shared_from_this());
    }

    return results;
}

Tuple Plane::local_normal_at(const Tuple &local_point, const Intersection& intersection) const {
    return Tuple::vector(0, 1, 0);
}

Bounds Plane::bounds() const {
    return Bounds(-INFINITY, INFINITY, 0, 0, -INFINITY, INFINITY);
}
