#pragma once

#include <iostream>

class Color {

public:
    float r, g, b;

    Color(float r, float g, float b);
    Color();

    Color operator +(Color other) const;
    Color operator -(Color other) const;
    Color operator *(Color other) const;

    Color operator *(float scalar) const;
    Color operator /(float scalar) const;

    bool operator ==(Color other) const;

    static const Color black;
    static const Color white;

};

std::ostream& operator <<(std::ostream& stream, const Color& tuple);
