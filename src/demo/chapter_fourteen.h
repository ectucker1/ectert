#pragma once

#include "world/camera.h"
#include "files/ppm.h"
#include "shapes/cylinder.h"
#include "shapes/sphere.h"
#include "math/transform.h"
#include "shapes/group.h"
#include <cmath>

std::shared_ptr<Shape> hexagon_corner() {
    return std::make_shared<Sphere>(translation(0, 0, -1) * scaling(0.25, 0.25, 0.25));
}

std::shared_ptr<Shape> hexagon_edge() {
    auto edge = std::make_shared<Cylinder>();
    edge->minimum = 0;
    edge->maximum = 1;
    edge->transform(translation(0, 0, -1) * rotation_y(-M_PI / 6) * rotation_z(-M_PI_2) * scaling(0.25, 1, 0.25));
    return edge;
}

std::shared_ptr<Shape> hexagon_side() {
    auto edge = std::make_shared<Group>();
    edge->add_child(hexagon_corner());
    edge->add_child(hexagon_edge());
    return edge;
}

std::shared_ptr<Shape> hexagon() {
    auto hex = std::make_shared<Group>();

    for (int i = 0; i < 6; i++) {
        auto side = hexagon_side();
        side->transform(rotation_y(i * M_PI / 3));
        hex->add_child(side);
    }

    return hex;
}

void run_chapter_fourteen() {
    World world = World();

    for (int i = 0; i < 10; i++) {
        auto hex = hexagon();
        hex->transform(translation(0, 1.25 * i - 6, 0) * rotation_y(i % 2 * M_PI_2) * rotation_x(M_PI_2));
        world.objects.push_back(hex);
    }

    world.lights.emplace_back(Tuple::point(-10, 10, -10), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(1920, 1080, M_PI / 3);
    cam.transform(view_transform(Tuple::point(2, 5, -12), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = cam.render(world);
    write_ppm(canvas, "chapter14.ppm");
}