#pragma once

#include "math/color.h"

class Canvas {

private:
    Color* pixels;

    int index(int x, int y) const;

public:
    int width, height;

    Canvas(int width, int height);
    ~Canvas();

    void write_pixel(int x, int y, Color color);
    Color get_pixel(int x, int y) const;

};
