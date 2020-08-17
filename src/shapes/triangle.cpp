#include "triangle.h"
#include "math/bounds.h"
#include <algorithm>

Triangle::Triangle(Tuple p1, Tuple p2, Tuple p3)
    : _p1(p1), _p2(p2), _p3(p3), _e1(p2 - p1), _e2(p3 - p1), _n1(_e2.cross(_e1).normalized()), _n2(_n1), _n3(_n1) {}

Triangle::Triangle(Tuple p1, Tuple p2, Tuple p3, Tuple n1, Tuple n2, Tuple n3)
        : _p1(p1), _p2(p2), _p3(p3), _e1(p2 - p1), _e2(p3 - p1), _n1(n1), _n2(n2), _n3(n3) {}

Tuple Triangle::p1() const {
    return _p1;
}

Tuple Triangle::p2() const {
    return _p2;
}

Tuple Triangle::p3() const {
    return _p3;
}

Tuple Triangle::e1() const {
    return _e1;
}

Tuple Triangle::e2() const {
    return _e2;
}

Tuple Triangle::n1() const {
    return _n1;
}

Tuple Triangle::n2() const {
    return _n2;
}

Tuple Triangle::n3() const {
    return _n3;
}

std::vector<Intersection> Triangle::local_intersect(const Ray& local_ray) const {
    // Möller–Trumbore Triangle intersection algorithm
    Tuple dir_cross_e2 = local_ray.direction.cross(_e2);
    float det = _e1.dot(dir_cross_e2);

    // Ray is parallel to triangle
    if (std::abs(det) < 0.01)
        return {};

    float f = 1.0f / det;
    Tuple p1_to_origin = local_ray.origin - _p1;
    float u = f * p1_to_origin.dot(dir_cross_e2);

    // Ray misses on p1-p3 edge
    if (u < 0 || u > 1)
        return {};

    Tuple origin_cross_e1 = p1_to_origin.cross(_e1);
    float v = f * local_ray.direction.dot(origin_cross_e1);

    // Ray misses on p1-p2 or p2-p3 edge
    if (v < 0 || (u + v) > 1)
        return {};

    // We have actually hit! Find t
    float t = f * _e2.dot(origin_cross_e1);
    return {Intersection(t, shared_from_this(), u, v)};
}

Tuple Triangle::local_normal_at(const Tuple& local_point, const Intersection& intersection) const {
    return _n2 * intersection.u + _n3 * intersection.v + _n1 * (1 - intersection.u - intersection.v);
}

Bounds Triangle::bounds() const {
    return Bounds(std::min({_p1.x, _p2.x, _p3.x}), std::max({_p1.x, _p2.x, _p3.x}),
        std::min({_p1.y, _p2.y, _p3.y}), std::max({_p1.y, _p2.y, _p3.y}),
        std::min({_p1.z, _p2.z, _p3.z}), std::max({_p1.z, _p2.z, _p3.z}));
}
