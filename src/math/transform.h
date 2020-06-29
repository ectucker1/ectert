#pragma once

#include "matrix.h"

Matrix translation(float x, float y, float z);

Matrix scaling(float x, float y, float z);

Matrix rotation_x(float r);
Matrix rotation_y(float r);
Matrix rotation_z(float r);

Matrix shearing(float x_y, float x_z, float y_x, float y_z, float z_x, float z_y);
