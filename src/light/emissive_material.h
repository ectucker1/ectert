#pragma once

#include "material.h"

class EmissiveMaterial : public Material {

public:
    Color emission;

    EmissiveMaterial();
    EmissiveMaterial(Color emitted);

    virtual Scatter scatter(const Hit& hit) const;
    virtual Color emitted(const Hit& hit) const;

};
