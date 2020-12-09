#pragma once

#include "material.h"

class LambertianMaterial : public Material {

public:
    Color albedo;

    LambertianMaterial();
    LambertianMaterial(const Color& albedo);

    virtual Scatter scatter(const Hit& hit) const;

};
