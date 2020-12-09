#pragma once

#include "material.h"

class DielectricMaterial : public Material {

public:
    DielectricMaterial(float ior);

    virtual Scatter scatter(const Hit& hit) const;

private:
    static Tuple refract(const Tuple& incoming, const Tuple& normal, float n_ratio);
    static float reflectance(float cosine, float n_ratio);

};
