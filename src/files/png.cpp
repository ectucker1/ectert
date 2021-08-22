#include "png.h"

#include "stb_image_write.h"
#include "canvas.h"

void write_png(const Canvas& canvas, const std::string& path) {
    int width = canvas.width;
    int height = canvas.height;
    int stride = width * 3;

    auto pixels = new unsigned char[width * height * 3] { 255 };

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Color color = canvas.get_pixel(x, y);
            pixels[stride * y + 3 * x + 0] = encode_color(color.r);
            pixels[stride * y + 3 * x + 1] = encode_color(color.g);
            pixels[stride * y + 3 * x + 2] = encode_color(color.b);
        }
    }

    // 3 = RGB
    stbi_write_png(path.c_str(), width, height, 3, pixels, stride);

    delete[] pixels;
}

unsigned char encode_color(float color) {
    if (color >= 1.0) {
        return 255;
    } else if (color <= 0.0) {
        return 0;
    } else {
        return (unsigned char) (255 * color);
    }
}
