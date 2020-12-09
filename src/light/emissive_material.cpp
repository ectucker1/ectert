#include "emissive_material.h"

#include "light/scatter.h"
#include "intersection/hit.h"

EmissiveMaterial::EmissiveMaterial() : emission(Color()) {}

EmissiveMaterial::EmissiveMaterial(Color emission) : emission(emission) {}

Scatter EmissiveMaterial::scatter(const Hit &hit) const {
    return {Ray(Tuple(), Tuple()), Color(), true};
}

Color EmissiveMaterial::emitted(const Hit &hit) const {
    return emission;
}
