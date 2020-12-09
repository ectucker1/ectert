#pragma once

#include "shapes/sphere.h"
#include "light/dielectric_material.h"
#include <memory>

static std::shared_ptr<Sphere> test_glass_sphere() {
    auto sphere = std::make_shared<Sphere>();
    auto material = std::make_shared<DielectricMaterial>(1.5);
    sphere->material = material;
    return sphere;
}
