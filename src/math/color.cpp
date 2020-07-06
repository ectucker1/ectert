#include "color.h"
#include "float_util.h"

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color::Color() : r(0), g(0), b(0) {}

Color Color::operator +(Color other) const {
    return {r + other.r, g + other.g, b + other.b};
}

Color Color::operator -(Color other) const {
    return {r - other.r, g - other.g, b - other.b};
}

Color Color::operator *(Color other) const {
    return {r * other.r, g * other.g, b * other.b};
}

Color Color::operator *(float scalar) const {
    return {r * scalar, g * scalar, b * scalar};
}

Color Color::operator /(float scalar) const {
    return {r / scalar, g / scalar, b / scalar};
}

bool Color::operator ==(const Color other) const {
    return float_equal(r, other.r) && float_equal(g, other.g) && float_equal(b, other.b);
}

std::ostream& operator <<(std::ostream &stream, const Color& color) {
    stream << "<" << color.r << ", " << color.g << ", " << color.b << ">";
    return stream;
}
