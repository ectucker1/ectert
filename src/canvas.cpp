#include "canvas.h"

Canvas::Canvas(int width, int height) : width(width), height(height) {
    pixels = new Color[width * height] {Color(0, 0, 0)};
}

Canvas::~Canvas() {
    delete[] pixels;
}

int Canvas::index(int x, int y) {
    return x + y * width;
}

void Canvas::write_pixel(int x, int y, Color color) {
    if (x < 0 || x >= width) {
        throw std::out_of_range("X position must be within range");
    }
    if (y < 0 || y >= height) {
        throw std::out_of_range("Y position must be within range");
    }
    pixels[index(x, y)] = color;
}

Color Canvas::get_pixel(int x, int y) {
    if (x < 0 || x >= width) {
        throw std::out_of_range("X position must be within range");
    }
    if (y < 0 || y >= height) {
        throw std::out_of_range("Y position must be within range");
    }
    return pixels[index(x, y)];
}
