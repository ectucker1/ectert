#pragma once

#include "world/camera.h"
#include "files/ppm.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"
#include "math/transform.h"
#include <cmath>

void run_chapter_nine() {
    World world = World();

    Material wallMaterial = Material();
    wallMaterial.color = Color(0xFF / 255.0, 0x00 / 255.0, 0x00 / 255.0);
    wallMaterial.diffuse = 1.0;
    wallMaterial.specular = 0.8;

    auto floor = std::make_shared<Plane>();
    floor->material = wallMaterial;
    floor->transform(translation(0, -4, 0));
    world.objects.push_back(floor);

    world.lights.emplace_back(Tuple::point(0, 0, -10), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(512, 256, M_PI / 3);
    cam.transform(view_transform(Tuple::point(0, 0, -5), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = cam.render(world);
    write_ppm(canvas, "chapter9.ppm");
}