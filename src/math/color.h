#pragma once

#include <iostream>
#include "float_util.h"

class Color {

public:
    float r, g, b;

    inline Color(float r, float g, float b) : r(r), g(g), b(b) {}

    inline Color() : r(0), g(0), b(0) {}

    inline Color operator +(Color other) const {
        return {r + other.r, g + other.g, b + other.b};
    }

    inline Color operator -(Color other) const {
        return {r - other.r, g - other.g, b - other.b};
    }

    inline Color operator *(Color other) const {
        return {r * other.r, g * other.g, b * other.b};
    }

    inline Color operator *(float scalar) const {
        return {r * scalar, g * scalar, b * scalar};
    }

    inline Color operator /(float scalar) const {
        return {r / scalar, g / scalar, b / scalar};
    }

    inline bool operator ==(const Color other) const {
        return float_equal(r, other.r) && float_equal(g, other.g) && float_equal(b, other.b);
    }

    static const Color white;
    static const Color black;
};

inline std::ostream& operator <<(std::ostream &stream, const Color& color) {
    stream << "<" << color.r << ", " << color.g << ", " << color.b << ">";
    return stream;
}
