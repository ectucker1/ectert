#include "cylinder.h"
#include "math/bounds.h"
#include <cmath>

Cylinder::Cylinder() {};

Cylinder::Cylinder(const Matrix &transform) : Shape(transform) {}

std::vector<Intersection> Cylinder::local_intersect(const Ray &local_ray) const {
    float a = local_ray.direction.x * local_ray.direction.x + local_ray.direction.z * local_ray.direction.z;

    std::vector<Intersection> xs = {};

    // Check intersection with walls only if ray is not parallel
    if (std::abs(a) > 0.001) {
        float b = 2 * local_ray.origin.x * local_ray.direction.x + 2 * local_ray.origin.z * local_ray.direction.z;
        float c = local_ray.origin.x * local_ray.origin.x + local_ray.origin.z * local_ray.origin.z - 1;

        float disc = b * b - 4 * a * c;

        // Ray misses cylinder
        if (disc < 0) return xs;

        float sqrt_disc = std::sqrt(disc);

        float t0 = (-b - sqrt_disc) / (2 * a);
        float t1 = (-b + sqrt_disc) / (2 * a);

        // Ensure hits in right order
        if (t0 > t1)
            std::swap(t0, t1);

        // Only keep hits within range of cylinder

        float y0 = local_ray.origin.y + t0 * local_ray.direction.y;
        if (minimum < y0 && y0 < maximum)
            xs.emplace_back(t0, shared_from_this());

        float y1 = local_ray.origin.y + t1 * local_ray.direction.y;
        if (minimum < y1 && y1 < maximum)
            xs.emplace_back(t1, shared_from_this());
    }

    intersect_caps(local_ray, xs);

    return xs;
}

Tuple Cylinder::local_normal_at(const Tuple& local_point) const {
    // Square of distance from y axis
    float dist = local_point.x * local_point.x + local_point.z * local_point.z;

    if (dist < 1 && local_point.y >= maximum - 0.001) {
        return Tuple::vector(0, 1, 0);
    } else if (dist < 1 && local_point.y <= minimum + 0.001) {
        return Tuple::vector(0, -1, 0);
    } else {
        return Tuple::vector(local_point.x, 0, local_point.z);
    }
}

// Check if intersection t is within a radius of 1 from y axis
bool Cylinder::check_caps(const Ray& local_ray, const float t) const {
    float x = local_ray.origin.x + local_ray.direction.x * t;
    float z = local_ray.origin.z + local_ray.direction.z * t;
    return (x * x + z * z) < 1 + 0.001;
}

void Cylinder::intersect_caps(const Ray& local_ray, std::vector<Intersection>& xs) const {
    // Don't check caps if cylinder isn't closed or ray is not at all parallel to cylinder
    if (!closed || std::abs(local_ray.direction.y) < 0.001)
        return;

    // Check for intersection with plane at y = minimum
    float t0 = (minimum - local_ray.origin.y) / local_ray.direction.y;
    if (check_caps(local_ray, t0)) {
        xs.emplace_back(t0, shared_from_this());
    }

    // Check for intersection ay y = maximum
    float t1 = (maximum - local_ray.origin.y) / local_ray.direction.y;
    if (check_caps(local_ray, t1)) {
        xs.emplace_back(t1, shared_from_this());
    }
}

Bounds Cylinder::bounds() const {
    return Bounds(-1, 1, minimum, maximum, -1, 1);
}
