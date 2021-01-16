#pragma once

#include "math/color.h"

class Canvas {

private:
    Color* pixels;
    unsigned char* image_data;

    int index_pixel(int x, int y) const;
    int index_image(int x, int y, int bit) const;

public:
    int width, height;

    Canvas(int width, int height);
    ~Canvas();

    void write_pixel(int x, int y, Color color);
    Color get_pixel(int x, int y) const;

    unsigned char* image() const;

};
