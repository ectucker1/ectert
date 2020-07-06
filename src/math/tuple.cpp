#include "tuple.h"
#include "float_util.h"
#include <cmath>

Tuple::Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Tuple Tuple::point(float x, float y, float z) {
    return {x, y, z, 1};
}

Tuple Tuple::vector(float x, float y, float z) {
    return {x, y, z, 0};
}

bool Tuple::is_point() const {
    return float_equal(w, 1);
}

bool Tuple::is_vector() const {
    return float_equal(w, 0);
}

Tuple Tuple::operator +(Tuple other) const {
    return {x + other.x, y + other.y, z + other.z, w + other.w};
}

Tuple Tuple::operator -(Tuple other) const {
    return {x - other.x, y - other.y, z - other.z, w - other.w};
}

Tuple Tuple::operator *(float scalar) const {
    return {x * scalar, y * scalar, z * scalar, w * scalar};
}

Tuple Tuple::operator /(float scalar) const {
    return {x / scalar, y / scalar, z / scalar, w / scalar};
}

Tuple Tuple::operator-() const {
    return {-x, -y, -z, -w};
}

float Tuple::magnitude_sq() const {
    return x * x + y * y + z * z + w * w;
}

float Tuple::magnitude() const {
    return sqrt(x * x + y * y + z * z + w * w);
}

Tuple Tuple::normalized() const {
    float magnitude = this->magnitude();
    return {x / magnitude, y / magnitude, z / magnitude, w / magnitude};
}

float Tuple::dot(Tuple other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Tuple Tuple::cross(Tuple other) const {
    return Tuple::vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

Tuple Tuple::reflect(Tuple normal) const {
    return Tuple(x, y, z, w) - normal * 2 * dot(normal);
}

bool Tuple::operator ==(const Tuple other) const {
    return float_equal(x, other.x) && float_equal(y, other.y)
        && float_equal(z, other.z) && float_equal(w, other.w);
}

std::ostream& operator <<(std::ostream &stream, const Tuple& tuple) {
    stream << "<" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w << ">";
    return stream;
}
