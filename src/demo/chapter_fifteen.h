#pragma once

#include "world/camera.h"
#include "files/ppm.h"
#include "shapes/triangle.h"
#include "math/transform.h"
#include "files/obj.h"
#include <chrono>
#include <cmath>

void run_chapter_fifteen() {
    World world = World();

    auto model = load_obj_group("../../assets/teapot.obj");
    model->transform(translation(0, -1.75, 0) * rotation_x(-M_PI_2) * scaling(0.25, 0.25, 0.25));
    world.objects.push_back(model);

    world.lights.emplace_back(Tuple::point(2, 2, -8), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(2048, 1024, M_PI / 3);
    cam.transform(view_transform(Tuple::point(2, 2, -8), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = cam.render(world);
    write_ppm(canvas, "chapter15.ppm");
}
