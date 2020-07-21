#pragma once

#include "world/camera.h"
#include "files/ppm.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"
#include "math/transform.h"
#include "pattern/checker_pattern.h"
#include <cmath>

void run_chapter_ten() {
    World world = World();

    Material wallMaterial = Material();
    wallMaterial.color = Color(0xFF / 255.0, 0x00 / 255.0, 0x00 / 255.0);
    wallMaterial.pattern = std::make_shared<CheckerPattern>(Color::white, Color::black);

    auto floor = std::make_shared<Plane>();
    floor->material = wallMaterial;
    floor->transform(translation(0, -4, 0));
    world.objects.push_back(floor);

    world.lights.emplace_back(Tuple::point(0, 0, -10), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(1024, 512, M_PI / 3);
    cam.transform(view_transform(Tuple::point(0, 0, -5), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = cam.render(world);
    write_ppm(canvas, "chapter10.ppm");
}
