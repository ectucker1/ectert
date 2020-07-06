#pragma once

#include "math/tuple.h"
#include "math/color.h"

class PointLight {

public:
    Tuple position;
    Color intensity;

    PointLight(Tuple position, Color intensity);

};
