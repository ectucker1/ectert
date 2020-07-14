#include "intersection.h"
#include <cmath>
#include <algorithm>

Intersection::Intersection(float t, const std::shared_ptr<const Shape> object) : t(t), object(object) {}

const Intersection Intersection::NIL = Intersection(-INFINITY, std::shared_ptr<Shape>());

bool Intersection::operator==(const Intersection &other) const {
    return t == other.t && object == other.object;
}

bool Intersection::operator<(const Intersection &other) const {
    return t < other.t;
}

std::vector<Intersection> sort_intersections(std::vector<Intersection>& values) {
    std::sort(values.begin(), values.end());
    return values;
}

Intersection hit(std::vector<Intersection>& list) {
    for (Intersection intersection : list) {
        if (intersection.t >= 0) {
            return intersection;
        }
    }
    return Intersection::NIL;
}
