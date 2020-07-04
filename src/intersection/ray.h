#pragma once

#include "math/tuple.h"
#include "math/matrix.h"

class Ray {

public:
    Tuple origin;
    Tuple direction;

    Ray(Tuple origin, Tuple direction);

    Tuple position(const float t) const;

    Ray transform(const Matrix& matrix) const;

};
