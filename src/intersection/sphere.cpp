#include "sphere.h"
#include <cmath>

Sphere::Sphere() : _transform(Matrix::identity()), _inverse(_transform.inverse()) {}
Sphere::Sphere(const Matrix& transform) : _transform(transform), _inverse(_transform.inverse()) {}

Matrix Sphere::transform() {
    return _transform;
}

void Sphere::transform(const Matrix& trans) {
    _transform = trans;
    _inverse = trans.inverse();
}

Matrix Sphere::inverse() {
    return _inverse;
}

std::vector<Intersection> Sphere::intersect(Ray ray) {
    ray = ray.transform(_inverse);

    Tuple sphereToRay = ray.origin - Tuple::point(0, 0, 0);

    float a = ray.direction.dot(ray.direction);
    float b = 2 * ray.direction.dot(sphereToRay);
    float c = sphereToRay.dot(sphereToRay) - 1;

    float discriminant = b * b - 4 * a * c;

    std::vector<Intersection> results = std::vector<Intersection>();
    if (discriminant >= 0) {
        results.emplace_back(Intersection((-b - std::sqrt(discriminant)) / (2 * a), this));
        results.emplace_back(Intersection((-b + std::sqrt(discriminant)) / (2 * a), this));
    }

    return intersection_list(results);
}

Tuple Sphere::normal_at(Tuple point) const {
    point = _inverse * point;
    Tuple normal = _inverse.transposed() * Tuple::vector(point.x, point.y, point.z);
    normal.w = 0;
    return normal.normalized();
}

bool Sphere::operator==(const Sphere &other) const {
    return true;
}
