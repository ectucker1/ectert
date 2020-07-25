#pragma once

#include "world/camera.h"
#include "files/ppm.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"
#include "math/transform.h"
#include <cmath>

void run_chapter_eleven() {
    World world = World();

    Material wallMaterial = Material();
    wallMaterial.color = Color(0, 0, 0);
    wallMaterial.diffuse = 0.8;
    wallMaterial.specular = 0.1;
    wallMaterial.reflectivity = 0.4;

    Material leftMaterial = Material();
    leftMaterial.color = Color(0xED / 255.0, 0x00 / 255.0, 0x8C / 255.0);
    leftMaterial.diffuse = 0.8;
    leftMaterial.specular = 0.9;

    Material centerMaterial = Material();
    centerMaterial.color = Color(0xDA / 255.0, 0xF3 / 255.0, 0xEC / 255.0);
    centerMaterial.diffuse = 0.8;
    centerMaterial.specular = 0.9;

    Material rightMaterial = Material();
    rightMaterial.color = Color(0x00 / 255.0, 0xBF / 255.0, 0xF3 / 255.0);
    rightMaterial.diffuse = 0.8;
    rightMaterial.specular = 0.9;

    auto floor = std::make_shared<Sphere>(scaling(10, 0.01, 10));
    floor->material = wallMaterial;
    auto leftWall = std::make_shared<Sphere>(translation(0, 0, 5) * rotation_y(-M_PI_4) * rotation_x(M_PI_2) * scaling(10, 0.01, 10));
    leftWall->material = wallMaterial;
    auto rightWall = std::make_shared<Sphere>(translation(0, 0, 5) * rotation_y(M_PI_4) * rotation_x(M_PI_2) * scaling(10, 0.01, 10));
    rightWall->material = wallMaterial;

    auto left = std::make_shared<Sphere>(translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33));
    left->material = leftMaterial;
    auto center = std::make_shared<Sphere>(translation(-0.5, 1, 0.5));
    center->material = centerMaterial;
    auto right = std::make_shared<Sphere>(translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
    right->material = rightMaterial;

    world.objects.push_back(floor);
    world.objects.push_back(leftWall);
    world.objects.push_back(rightWall);
    world.objects.push_back(center);
    world.objects.push_back(right);
    world.objects.push_back(left);

    world.lights.emplace_back(Tuple::point(-10, 10, -10), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(2048, 1024, M_PI / 3);
    cam.transform(view_transform(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = cam.render(world);
    write_ppm(canvas, "chapter11.ppm");
}
