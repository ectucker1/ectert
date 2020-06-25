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

    bool operator ==(Color other) const;

};

std::ostream& operator <<(std::ostream& stream, const Color& tuple);
