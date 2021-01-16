#include "canvas.h"

#include "files/png.h"

Canvas::Canvas(int width, int height) : width(width), height(height) {
    pixels = new Color[width * height] {Color(0, 0, 0)};
    image_data = new unsigned char[width * height * 4] { 0 };
}

Canvas::~Canvas() {
    delete[] pixels;
    delete[] image_data;
}

int Canvas::index_pixel(int x, int y) const {
    return x + y * width;
}

int Canvas::index_image(int x, int y, int bit) const {
    return bit + (x + width * y) * 4;
}

void Canvas::write_pixel(int x, int y, Color color) {
    if (x < 0 || x >= width) {
        throw std::out_of_range("X position must be within range");
    }
    if (y < 0 || y >= height) {
        throw std::out_of_range("Y position must be within range");
    }
    pixels[index_pixel(x, y)] = color;
    image_data[index_image(x, y, 0)] = encode_color(color.r);
    image_data[index_image(x, y, 1)] = encode_color(color.g);
    image_data[index_image(x, y, 2)] = encode_color(color.b);
    image_data[index_image(x, y, 3)] = 255;
}

Color Canvas::get_pixel(int x, int y) const {
    if (x < 0 || x >= width) {
        throw std::out_of_range("X position must be within range");
    }
    if (y < 0 || y >= height) {
        throw std::out_of_range("Y position must be within range");
    }
    return pixels[index_pixel(x, y)];
}

unsigned char *Canvas::image() const {
    return image_data;
}
