#include "sphere.h"
#include "math/bounds.h"
#include <cmath>

Sphere::Sphere() : Shape() {}
Sphere::Sphere(const Matrix& transform) : Shape(transform) {}

std::vector<Intersection> Sphere::local_intersect(const Ray &local_ray) const {
    Tuple sphereToRay = local_ray.origin - Tuple::point(0, 0, 0);

    float a = local_ray.direction.dot(local_ray.direction);
    float b = 2 * local_ray.direction.dot(sphereToRay);
    float c = sphereToRay.dot(sphereToRay) - 1;

    float discriminant = b * b - 4 * a * c;

    std::vector<Intersection> results = std::vector<Intersection>();
    if (discriminant >= 0) {
        results.emplace_back(Intersection((-b - std::sqrt(discriminant)) / (2 * a), shared_from_this()));
        results.emplace_back(Intersection((-b + std::sqrt(discriminant)) / (2 * a), shared_from_this()));
    }

    return sort_intersections(results);
}

Tuple Sphere::local_normal_at(const Tuple &local_point, const Intersection& intersection) const {
    return Tuple::vector(local_point.x, local_point.y, local_point.z);
}

bool Sphere::operator==(const Sphere &other) const {
    return true;
}

Bounds Sphere::bounds() const {
    return Bounds(-1, 1, -1, 1, -1, 1);
}
