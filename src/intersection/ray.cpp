#include "ray.h"

Ray::Ray(Tuple origin, Tuple direction) : origin(origin), direction(direction) {}

Tuple Ray::position(const float t) const {
    return origin + direction * t;
}

Ray Ray::transform(const Matrix &matrix) const {
    return Ray(matrix * origin, matrix * direction);
}
