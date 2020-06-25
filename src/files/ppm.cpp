#include "ppm.h"

std::string clamp_color_float(float color) {
    if (color > 1.0) {
        return "255";
    } else if (color < 0.0) {
        return "0";
    } else {
        return std::to_string((int) (255 * color));
    }
}

std::string generate_ppm(Canvas& canvas) {
    std::string file = "P3\n";
    file += std::to_string(canvas.width) + " " + std::to_string(canvas.height) + "\n";
    file += std::to_string(255) + "\n";

    std::string line;
    for (int y = 0; y < canvas.height; y++) {
        for (int x = 0; x < canvas.width; x++) {
            Color color = canvas.get_pixel(x, y);
            if (line.length() > 66) {
                file += line + "\n";
                line = "";
            }
            line += clamp_color_float(color.r) + " ";
            if (line.length() > 66) {
                file += line + "\n";
                line = "";
            }
            line += clamp_color_float(color.g) + " ";
            if (line.length() > 66) {
                file += line + "\n";
                line = "";
            }
            line += clamp_color_float(color.b) + " ";
        }
        file += line + "\n";
        line = "";
    }
    return file;
}

void write_ppm(Canvas& canvas, const std::string& path) {
    std::ofstream out(path);
    out << generate_ppm(canvas);
    out.close();
}
