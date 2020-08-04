#pragma once

#include "world/camera.h"
#include "files/ppm.h"
#include "shapes/plane.h"
#include "shapes/cylinder.h"
#include "shapes/cone.h"
#include "math/transform.h"
#include <cmath>

void run_chapter_thirteen() {
    World world = World();

    Material floorMat = Material();
    floorMat.color = Color(0.6, 0.6, 0.6);
    floorMat.diffuse = 0.5;
    floorMat.specular = 0.9;
    floorMat.reflectivity = 0.5;
    floorMat.shininess = 400;
    Material objectMat = Material();
    objectMat.color = Color(0, 0, 1);
    objectMat.diffuse = 0.8;
    objectMat.specular = 0.3;
    objectMat.shininess = 300;

    auto floor = std::make_shared<Plane>(translation(0, -1, 0));
    floor->material = floorMat;
    auto cylinder = std::make_shared<Cylinder>();
    cylinder->material = objectMat;
    cylinder->minimum = -1;
    cylinder->maximum = 1;
    auto cone = std::make_shared<Cone>(translation(0, 3, 0) * scaling(1, 2, 1));
    cone->material = objectMat;
    cone->maximum = 0;
    cone->minimum = -1;

    world.objects.push_back(floor);
    world.objects.push_back(cylinder);
    world.objects.push_back(cone);

    world.lights.emplace_back(Tuple::point(-10, 10, -10), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(4096, 2048, M_PI / 3);
    cam.transform(view_transform(Tuple::point(2, 5, -12), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = cam.render(world);
    write_ppm(canvas, "chapter13.ppm");
}
