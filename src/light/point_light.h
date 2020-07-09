#pragma once

#include "math/tuple.h"
#include "math/color.h"

class PointLight {

public:
    Tuple position;
    Color intensity;

    static const PointLight NIL;

    PointLight(Tuple position, Color intensity);

    bool operator ==(const PointLight& other) const;

};
