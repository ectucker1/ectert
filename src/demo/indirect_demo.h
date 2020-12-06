#pragma once

#include "world/world.h"
#include "shapes/plane.h"
#include "math/transform.h"
#include "world/camera.h"
#include "files/png.h"
#include "light/lambertian_material.h"
#include "processing/render_process.h"
#include "shapes/sphere.h"
#include "light/gradient_background.h"
#include "light/metal_material.h"
#include "light/dielectric_material.h"
#include "light/emissive_material.h"

void run_indirect_demo() {
    World world = World();

    auto background = std::make_shared<GradientBackground>(Color(0.0, 0.0, 0.0), Color(0.05, 0.05, 0.05));

    auto left = std::make_shared<Sphere>(translation(-2.0, 0.0, 0.0));
    left->material = std::make_shared<DielectricMaterial>(1.5);

    auto center = std::make_shared<Sphere>(translation(0, 5, 0));
    center->material = std::make_shared<EmissiveMaterial>(Color(6, 6, 6));

    auto right = std::make_shared<Sphere>(translation(2.0, 0.0, 0.0));
    right->material = std::make_shared<MetalMaterial>(Color(0.8, 0.6, 0.2), 1.0);

    auto ground = std::make_shared<Plane>(translation(0, -1.0, 0));
    ground->material = std::make_shared<LambertianMaterial>(Color(0.5, 0.5, 0.5));

    world.background = background;
    world.objects.push_back(left);
    world.objects.push_back(center);
    world.objects.push_back(right);
    world.objects.push_back(ground);

    Camera cam = Camera(1024, 1024, M_PI / 3);
    cam.transform(view_transform(Tuple::point(-4, 4, -8), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = RenderProcess(8).render(cam, world, 16);

    write_png(canvas, "test_emissive.png");
}
