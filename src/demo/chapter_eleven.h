#pragma once

#include "world/camera.h"
#include "files/ppm.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"
#include "math/transform.h"
#include "pattern/striped_pattern.h"
#include <cmath>

void run_chapter_eleven() {
    World world = World();

    Material backgroundMat = Material();
    backgroundMat.pattern = std::make_shared<StripedPattern>(Color(0, 0, 0), Color(1, 1, 1));
    backgroundMat.pattern->transform(scaling(0.1, 0.1, 0.1));
    backgroundMat.diffuse = 0.8;
    backgroundMat.specular = 0.1;

    Material glassMat = Material();
    glassMat.color = Color(0.8, 0.8, 0.8);
    glassMat.diffuse = 0.01;
    glassMat.ambient = 0.2;
    glassMat.specular = 0.9;
    glassMat.shininess = 400;
    glassMat.alpha = 0.3;
    glassMat.reflectivity = 0.8;
    glassMat.ior = 1.52;

    Material waterMat = Material();
    waterMat.color = Color(0x00 / 255.0, 0x69 / 255.0, 0x94 / 255.0);
    waterMat.diffuse = 0.1;
    waterMat.ambient = 0.3;
    waterMat.specular = 0.9;
    waterMat.shininess = 200;
    waterMat.alpha = 0.3;
    waterMat.reflectivity = 0.8;
    waterMat.ior = 1.33;

    auto background = std::make_shared<Plane>(rotation_x(M_PI_2) * translation(0, 0, 1.5));
    background->material = backgroundMat;

    auto glass = std::make_shared<Sphere>(translation(0, 0, 0));
    glass->material = glassMat;

    auto water = std::make_shared<Sphere>(translation(0, 0, 0) * scaling(2, 2, 2));
    water->material = waterMat;

    world.objects.push_back(background);
    world.objects.push_back(glass);
    world.objects.push_back(water);

    world.lights.emplace_back(Tuple::point(-10, 10, -10), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(2048, 1024, M_PI / 3);
    cam.transform(view_transform(Tuple::point(0, 0, -10), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = cam.render(world);
    write_ppm(canvas, "chapter11.ppm");
}
