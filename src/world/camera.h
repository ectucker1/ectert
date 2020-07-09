#pragma once

#include "math/matrix.h"
#include "intersection/ray.h"
#include "canvas.h"
#include "world/world.h"
#include <cmath>

class Camera {

public:
    int hsize;
    int vsize;
    float fov;

    float half_width;
    float half_height;
    float pixel_size;

    Camera(int hsize, int vsize, float fov);

    Matrix transform();
    void transform(const Matrix& trans);

    Matrix inverse();

    Ray ray_to_pixel(int x, int y);

    Canvas render(const World& world);

private:
    Matrix _transform;
    Matrix _inverse;

};
