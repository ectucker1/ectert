#pragma once

class Canvas;

#include <string>

void write_png(const Canvas& canvas, const std::string& path);

unsigned char encode_color(float color);
