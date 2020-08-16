#pragma once

#include "world/camera.h"
#include "files/ppm.h"
#include "shapes/triangle.h"
#include "math/transform.h"
#include <cmath>

void run_chapter_fifteen() {
    World world = World();

    auto tri = std::make_shared<Triangle>(Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0), Tuple::point(0, 1, 0));
    world.objects.push_back(tri);

    world.lights.emplace_back(Tuple::point(-10, 10, -10), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(512, 256, M_PI / 3);
    cam.transform(view_transform(Tuple::point(2, 2, -8), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = cam.render(world);
    write_ppm(canvas, "chapter15.ppm");
}
