#include "lambertian_material.h"

#include "scatter.h"
#include "intersection/hit.h"
#include "math/rand_util.h"

LambertianMaterial::LambertianMaterial() : albedo(Color(1.0, 1.0, 1.0)) {}

LambertianMaterial::LambertianMaterial(const Color &albedo) : albedo(albedo) {}

Scatter LambertianMaterial::scatter(const Hit &hit) const {
    Tuple scatter_direction = hit.normalv + random_unit_vector();
    Ray scatter_ray = Ray(hit.over_point, scatter_direction);
    return {scatter_ray, albedo, false};
}
