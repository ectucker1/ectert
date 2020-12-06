#include "gradient_background.h"
#include "math/tuple.h"
#include "intersection/ray.h"

GradientBackground::GradientBackground(const Color &start, const Color &end) : start(start), end(end) {}

Color GradientBackground::sample_background(const Ray &ray) const {
    // Background generator inspired by https://raytracing.github.io/books/RayTracingInOneWeekend.html
    Tuple unit_direction = ray.direction.normalized();
    float t = 0.5f * (unit_direction.y + 1.0f);
    return end * (1.0f - t) + start * t;
}
