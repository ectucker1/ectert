#include "transform.h"
#include <cmath>

Matrix translation(float x, float y, float z) {
    Matrix result = Matrix::identity();
    result.set(0, 3, x);
    result.set(1, 3, y);
    result.set(2, 3, z);
    return result;
}

Matrix scaling(float x, float y, float z) {
    Matrix result = Matrix::identity();
    result.set(0, 0, x);
    result.set(1, 1, y);
    result.set(2, 2, z);
    return result;
}

Matrix rotation_x(float r) {
    Matrix result = Matrix::identity();
    result.set(1, 1, cosf(r));
    result.set(1, 2, -sinf(r));
    result.set(2, 1, sinf(r));
    result.set(2, 2, cosf(r));
    return result;
}

Matrix rotation_y(float r) {
    Matrix result = Matrix::identity();
    result.set(0, 0, cosf(r));
    result.set(0, 2, sinf(r));
    result.set(2, 0, -sinf(r));
    result.set(2, 2, cosf(r));
    return result;
}

Matrix rotation_z(float r) {
    Matrix result = Matrix::identity();
    result.set(0, 0, cosf(r));
    result.set(0, 1, -sinf(r));
    result.set(1, 0, sinf(r));
    result.set(1, 1, cosf(r));
    return result;
}

Matrix shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y) {
    Matrix result = Matrix::identity();
    result.set(0, 1, x_y);
    result.set(0, 2, x_z);
    result.set(1, 0, y_x);
    result.set(1, 2, y_z);
    result.set(2, 0, z_x);
    result.set(2, 1, z_y);
    return result;
}
