#pragma once

#include <iostream>
#include <cmath>
#include "math/float_util.h"

class Tuple {

public:
	float x, y, z, w;

    inline Tuple(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    inline Tuple() : x(0), y(0), z(0), w(0) {}

    inline static Tuple point(float x, float y, float z) {
        return {x, y, z, 1};
    }

    inline static Tuple vector(float x, float y, float z) {
        return {x, y, z, 0};
    }

    inline bool is_point() const {
        return float_equal(w, 1);
    }

    inline bool is_vector() const {
        return float_equal(w, 0);
    }

    inline Tuple operator +(Tuple other) const {
        return {x + other.x, y + other.y, z + other.z, w + other.w};
    }

    inline Tuple operator -(Tuple other) const {
        return {x - other.x, y - other.y, z - other.z, w - other.w};
    }

    inline Tuple operator *(float scalar) const {
        return {x * scalar, y * scalar, z * scalar, w * scalar};
    }

    inline Tuple operator /(float scalar) const {
        return {x / scalar, y / scalar, z / scalar, w / scalar};
    }

    inline Tuple operator-() const {
        return {-x, -y, -z, -w};
    }

    inline float magnitude_sq() const {
        return x * x + y * y + z * z + w * w;
    }

    inline float magnitude() const {
        return sqrtf(x * x + y * y + z * z + w * w);
    }

    inline Tuple normalized() const {
        float magnitude = this->magnitude();
        return {x / magnitude, y / magnitude, z / magnitude, w / magnitude};
    }

    inline float dot(Tuple other) const {
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    inline Tuple cross(Tuple other) const {
        return vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    inline Tuple reflect(Tuple normal) const {
        return Tuple(x, y, z, w) - normal * 2 * dot(normal);
    }

    inline bool operator ==(const Tuple other) const {
        return float_equal(x, other.x) && float_equal(y, other.y)
               && float_equal(z, other.z) && float_equal(w, other.w);
    }

};

inline std::ostream& operator <<(std::ostream &stream, const Tuple& tuple) {
    stream << "<" << tuple.x << ", " << tuple.y << ", " << tuple.z << ", " << tuple.w << ">";
    return stream;
}
