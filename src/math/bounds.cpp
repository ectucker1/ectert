#include "bounds.h"
#include "math/float_util.h"
#include "intersection/ray.h"
#include <algorithm>
#include <cmath>

Bounds::Bounds(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
    : minX(minX), maxX(maxX), minY(minY), maxY(maxY), minZ(minZ), maxZ(maxZ) {}

bool Bounds::operator==(const Bounds& other) const {
    return float_equal(minX, other.minX) && float_equal(maxX, other.maxX)
        && float_equal(minY, other.minY) && float_equal(maxY, other.maxY)
        && float_equal(minZ, other.minZ) && float_equal(maxZ, other.maxZ);
}

bool Bounds::intersects(const Ray& local_ray) const {
    if (infinite())
        return true;

    auto x_vals = check_axis(local_ray.origin.x, local_ray.direction.x, minX, maxX);
    auto y_vals = check_axis(local_ray.origin.y, local_ray.direction.y, minY, maxY);
    auto z_vals = check_axis(local_ray.origin.z, local_ray.direction.z, minZ, maxZ);

    float tmin = std::max({x_vals.first, y_vals.first, z_vals.first});
    float tmax = std::min({x_vals.second, y_vals.second, z_vals.second});

    return tmax >= tmin;
}

std::pair<float, float> Bounds::check_axis(float origin, float direction, float min, float max) const {
    float tmin_numerator = (min - origin);
    float tmax_numerator = (max - origin);

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

bool Bounds::infinite() const {
    return minX == -INFINITY || maxX == INFINITY
        || minY == -INFINITY || maxY == INFINITY
        || minZ == -INFINITY || maxZ == INFINITY;
}

std::ostream& operator <<(std::ostream &stream, const Bounds& bounds) {
    stream << "<" << bounds.minX << ", " << bounds.maxX << ", " << bounds.minY << ", " << bounds.maxY << ", " << bounds.minZ << ", " << bounds.maxZ << ">";
    return stream;
}
