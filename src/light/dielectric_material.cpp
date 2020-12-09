#include "dielectric_material.h"

#include "intersection/hit.h"
#include "light/scatter.h"
#include "math/rand_util.h"
#include <cmath>

DielectricMaterial::DielectricMaterial(float ior) {
    this->ior = ior;
}

Scatter DielectricMaterial::scatter(const Hit &hit) const {
    // Ratio of refractive indices
    float n_ratio = hit.n1 / hit.n2;

    Tuple unit_direction = hit.eyev.normalized();
    float cos_theta = fminf(unit_direction.dot(hit.normalv), 1.0);
    float sin_theta = sqrtf(1.0 - cos_theta * cos_theta);

    bool cannot_refract = n_ratio * sin_theta > 1.0;
    Ray scattered = Ray(Tuple(), Tuple());

    if (cannot_refract || hit.schlick_reflectance() >= random_float()) {
        scattered = Ray(hit.over_point, hit.reflectv);
    } else {
        scattered = Ray(hit.under_point, refract(unit_direction, hit.normalv, n_ratio));
    }

    return {scattered, Color(1.0, 1.0, 1.0), false};
}

Tuple DielectricMaterial::refract(const Tuple &eyev, const Tuple &normal, float n_ratio) {
    // See https://raytracing.github.io/books/RayTracingInOneWeekend.html for math
    float cos_theta = fminf(eyev.dot(normal), 1.0);
    Tuple r_out_perp = (normal * cos_theta - eyev) * n_ratio;
    Tuple r_out_parallel = normal * -sqrtf(fabsf(1.0f - r_out_perp.magnitude_sq()));
    return r_out_perp + r_out_parallel;
}

float DielectricMaterial::reflectance(float cosine, float n_ratio) {
    // Use Schlick's approximation for reflectance.
    float r0 = (1 - n_ratio) / (1 + n_ratio);
    r0 = r0 * r0;
    return r0 + (1 - r0) * powf((1 - cosine),5);
}