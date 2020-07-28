#pragma once

#include "shapes/sphere.h"
#include "light/material.h"
#include <memory>

static std::shared_ptr<Sphere> test_glass_sphere() {
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>();
    sphere->material.alpha = 0.0;
    sphere->material.ior = 1.5;
    return sphere;
}
