#include "metal_material.h"

#include "intersection/hit.h"
#include "light/scatter.h"
#include "math/rand_util.h"

MetalMaterial::MetalMaterial() : albedo(Color()), fuzz(1.0) {}

MetalMaterial::MetalMaterial(const Color &albedo, float fuzz) : albedo(albedo), fuzz(fuzz) {}

Scatter MetalMaterial::scatter(const Hit &hit) const {
    Ray scattered = Ray(hit.over_point, hit.reflectv + random_vector_in_unit_sphere() * fuzz);
    bool absorbed = scattered.direction.dot(hit.normalv) < 0;
    return {scattered, albedo, absorbed};
}
