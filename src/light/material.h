#pragma once

#include "math/color.h"
#include "math/tuple.h"
#include "light/point_light.h"
#include "pattern/pattern.h"
#include <memory>

class Material {

public:
    std::shared_ptr<Pattern> pattern;
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;

    Material();

    Color lighting(const std::shared_ptr<const Shape>& shape, const PointLight& light, const Tuple& position, const Tuple& eyev, const Tuple& normal, bool in_shadow) const;

    bool operator ==(const Material& other) const;

};
