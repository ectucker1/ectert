#include "cube.h"
#include "math/bounds.h"
#include <algorithm>
#include <cmath>

Cube::Cube() : Shape() {}

Cube::Cube(const Matrix &transform) : Shape(transform) {}

bool Cube::operator==(const Cube &other) const {
    return true;
}

std::vector<Intersection> Cube::local_intersect(const Ray &local_ray) const {
    auto x_vals = check_axis(local_ray.origin.x, local_ray.direction.x);
    auto y_vals = check_axis(local_ray.origin.y, local_ray.direction.y);
    auto z_vals = check_axis(local_ray.origin.z, local_ray.direction.z);

    float tmin = std::max({x_vals.first, y_vals.first, z_vals.first});
    float tmax = std::min({x_vals.second, y_vals.second, z_vals.second});

    if (tmin > tmax) {
        return std::vector<Intersection>();
    }

    return std::vector<Intersection>({Intersection(tmin, shared_from_this()),
                                      Intersection(tmax, shared_from_this())});
}

std::pair<float, float> Cube::check_axis(float origin, float direction) const {
    float tmin_numerator = (-1 - origin);
    float tmax_numerator = (1 - origin);

    float tmin;
    float tmax;
    if (std::abs(direction) > 0) {
        tmin = tmin_numerator / direction;
        tmax = tmax_numerator / direction;
    } else {
        tmin = tmin_numerator * INFINITY;
        tmax = tmax_numerator * INFINITY;
    }

    if (tmin > tmax) {
        std::swap(tmin, tmax);
    }

    return {tmin, tmax};
}

Tuple Cube::local_normal_at(const Tuple& local_point, const Intersection& intersection) const {
    Tuple point_abs = Tuple::point(std::abs(local_point.x), std::abs(local_point.y), std::abs(local_point.z));

    // Normal on cube points away from side this point is on
    if (point_abs.x >= point_abs.y && point_abs.x >= point_abs.z) {
        return Tuple::vector(local_point.x, 0, 0);
    } else if (point_abs.y >= point_abs.z) {
        return Tuple::vector(0, local_point.y, 0);
    } else {
        return Tuple::vector(0, 0, local_point.z);
    }
}

Bounds Cube::bounds() const {
    return Bounds(-1, 1, -1, 1, -1, 1);
}
