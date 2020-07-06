#pragma once

#include "math/color.h"
#include "math/tuple.h"
#include "light/point_light.h"

class Material {

public:
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;

    Material();

    Color lighting(const PointLight& light, const Tuple& position, const Tuple& eyev, const Tuple& normal) const;

    bool operator ==(const Material& other) const;

};
