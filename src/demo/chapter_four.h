#pragma once

#include "canvas.h"
#include "files/ppm.h"
#include "math/matrix.h"
#include "math/transform.h"
#include <cmath>

void run_chapter_four() {
    Canvas canvas = Canvas(120, 120);
    Color mark = Color(1, 1, 1);

    Tuple point = Tuple::point(0, 50, 0);
    Matrix rotation = rotation_z(M_PI / 6);
    for (int i = 0; i < 12; i++) {
        canvas.write_pixel(60 + (int) point.x, 60 + (int) point.y, mark);
        point = rotation * point;
    }

    write_ppm(canvas, "chapter4.ppm");
}
