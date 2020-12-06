#pragma once

#include "material.h"

class MetalMaterial : public Material {

public:
    Color albedo;
    float fuzz;

    MetalMaterial();
    MetalMaterial(const Color& albedo, float fuzz);

    virtual Scatter scatter(const Hit& hit) const;

};
