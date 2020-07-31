#pragma once

#include "world/camera.h"
#include "files/ppm.h"
#include "shapes/plane.h"
#include "shapes/cube.h"
#include "math/transform.h"
#include "pattern/striped_pattern.h"
#include <cmath>

void run_chapter_twelve() {
    World world = World();

    Material floorMat = Material();
    floorMat.color = Color(0.6, 0.6, 0.6);
    floorMat.reflectivity = 0.8;
    floorMat.diffuse = 0.2;
    floorMat.specular = 0.9;
    floorMat.shininess = 400;
    Material cubeMat = Material();
    cubeMat.color = Color(1, 0, 0);
    cubeMat.reflectivity = 0.5;
    cubeMat.diffuse = 0.5;
    cubeMat.specular = 0.7;
    cubeMat.shininess = 300;

    auto floor = std::make_shared<Plane>(translation(0, -1, 0));
    floor->material = floorMat;
    auto cube = std::make_shared<Cube>();
    cube->material = cubeMat;

    world.objects.push_back(floor);
    world.objects.push_back(cube);

    world.lights.emplace_back(Tuple::point(-10, 10, -10), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(2048, 1024, M_PI / 3);
    cam.transform(view_transform(Tuple::point(2, 2, -8), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = cam.render(world);
    write_ppm(canvas, "chapter12.ppm");
}
