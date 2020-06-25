#pragma once

#include "canvas.h"
#include <string>
#include <fstream>

std::string clamp_color_float(float color);

std::string generate_ppm(Canvas& canvas);

void write_ppm(Canvas& canvas, const std::string& path);
