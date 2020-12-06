#pragma once

#include "math/color.h"
#include "math/tuple.h"
#include "light/point_light.h"
#include "pattern/pattern.h"
#include <memory>

class Hit;
class Scatter;

class Material : public std::enable_shared_from_this<Material> {

public:
    float ior;

    Material();

    virtual Scatter scatter(const Hit& hit) const = 0;

    virtual bool operator ==(const Material& other) const;

};
