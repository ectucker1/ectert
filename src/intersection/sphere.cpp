#include "sphere.h"
#include <cmath>

Sphere::Sphere() : transform(Matrix::identity()) {}
Sphere::Sphere(const Matrix& transform) : transform(transform) {}

std::vector<Intersection> Sphere::intersect(Ray ray) {
    ray = ray.transform(transform.inverse());

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

bool Sphere::operator==(const Sphere &other) const {
    return true;
}
