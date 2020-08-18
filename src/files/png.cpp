#include "png.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
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
            pixels[stride * y + 3 * x + 0] = (unsigned char) (255 * color.r);
            pixels[stride * y + 3 * x + 1] = (unsigned char) (255 * color.g);
            pixels[stride * y + 3 * x + 2] = (unsigned char) (255 * color.b);
        }
    }

    // 3 = RGB
    stbi_write_png(path.c_str(), width, height, 3, pixels, stride);

    delete[] pixels;
}
