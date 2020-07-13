#pragma once

#include "world/camera.h"
#include "files/ppm.h"
#include "math/transform.h"

void run_chapter_seven() {
    World world = World();

    Material wallMaterial = Material();
    wallMaterial.color = Color(0xA7 / 255.0, 0xA2 / 255.0, 0x84 / 255.0);
    wallMaterial.diffuse = 0.8;
    wallMaterial.specular = 0.1;

    Material leftMaterial = Material();
    leftMaterial.color = Color(0x7C / 255.0, 0x90 / 255.0, 0x82 / 255.0);
    leftMaterial.diffuse = 0.8;
    leftMaterial.specular = 0.1;

    Material centerMaterial = Material();
    centerMaterial.color = Color(0x76 / 255.0, 0x6D / 255.0, 0x19 / 255.0);
    centerMaterial.diffuse = 0.8;
    centerMaterial.specular = 0.1;

    Material rightMaterial = Material();
    rightMaterial.color = Color(0xD0 / 255.0, 0xC8 / 255.0, 0x8E / 255.0);
    rightMaterial.diffuse = 0.8;
    rightMaterial.specular = 0.1;

    Sphere floor = Sphere(scaling(10, 0.01, 10));
    floor.material = wallMaterial;
    Sphere leftWall = Sphere(translation(0, 0, 5) * rotation_y(-M_PI_4) * rotation_x(M_PI_2) * scaling(10, 0.01, 10));
    leftWall.material = wallMaterial;
    Sphere rightWall = Sphere(translation(0, 0, 5) * rotation_y(M_PI_4) * rotation_x(M_PI_2) * scaling(10, 0.01, 10));
    rightWall.material = wallMaterial;

    Sphere left = Sphere(translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33));
    left.material = leftMaterial;
    Sphere center = Sphere(translation(-0.5, 1, 0.5));
    center.material = centerMaterial;
    Sphere right = Sphere(translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
    right.material = rightMaterial;

    world.objects.push_back(floor);
    world.objects.push_back(leftWall);
    world.objects.push_back(rightWall);
    world.objects.push_back(center);
    world.objects.push_back(right);
    world.objects.push_back(left);

    world.lights.emplace_back(Tuple::point(-10, 10, -10), Color(0.8, 0.8, 0.8));
    world.lights.emplace_back(Tuple::point(10, 10, -10), Color(0.2, 0.2, 0.2));

    Camera cam = Camera(1024, 512, M_PI / 3);
    cam.transform(view_transform(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = cam.render(world);
    write_ppm(canvas, "chapter7.ppm");
}