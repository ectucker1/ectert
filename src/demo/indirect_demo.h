#include "world/world.h"
#include "shapes/plane.h"
#include "math/transform.h"
#include "world/camera.h"
#include "files/png.h"
#include "light/lambertian_material.h"
#include "processing/render_process.h"
#include "shapes/sphere.h"
#include "light/gradient_background.h"

#pragma once

void run_indirect_demo() {
    World world = World();

    auto background = std::make_shared<GradientBackground>(Color(0.5, 0.7, 1.0), Color(1.0, 1.0, 1.0));
    auto sphere = std::make_shared<Sphere>();
    sphere->material = std::make_shared<LambertianMaterial>(Color(0.0, 1.0, 0.0));
    auto ground = std::make_shared<Plane>(translation(0, -1.0, 0));
    ground->material = std::make_shared<LambertianMaterial>(Color(0.5, 0.5, 0.5));

    world.background = background;
    world.objects.push_back(sphere);
    world.objects.push_back(ground);

    world.lights.emplace_back(Tuple::point(2, 2, -8), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(256, 256, M_PI / 3);
    cam.transform(view_transform(Tuple::point(2, 2, -8), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = RenderProcess(8).render(cam, world, 4);

    write_png(canvas, "test_diffuse4.png");
}