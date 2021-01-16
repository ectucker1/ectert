#pragma once

#include "math/matrix.h"
#include "intersection/ray.h"
#include "canvas.h"
#include "world/world.h"
#include <cmath>
#include <random>

class Camera {

public:
    Camera(int hsize, int vsize, float fov);

    Matrix transform() const;
    void transform(const Matrix& trans);

    int hsize() const;
    void hsize(const float& hsize);

    int vsize() const;
    void vsize(const float& vsize);

    Matrix inverse();

    Ray ray_to_pixel(int x, int y) const;
    Ray ray_to_strata(int pixelX, int pixelY, int strataX, int strataY, int numStrata);

    Canvas render(const World& world) const;

private:
    int _hsize;
    int _vsize;
    float fov;

    float half_width;
    float half_height;
    float pixel_size;

    Matrix _transform;
    Matrix _inverse;

    std::mt19937 _generator;
    std::uniform_real_distribution<float> _dist;

    void recalc_dimens();

};
