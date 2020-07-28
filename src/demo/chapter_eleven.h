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

    Material wallMaterial = Material();
    wallMaterial.pattern = std::make_shared<StripedPattern>(Color(0, 0, 0), Color(1, 1, 1));
    wallMaterial.pattern->transform(scaling(0.1, 0.1, 0.1));
    wallMaterial.diffuse = 0.8;
    wallMaterial.specular = 0.1;

    Material centerMaterial = Material();
    centerMaterial.color = Color(0xDA / 255.0, 0xF3 / 255.0, 0xEC / 255.0);
    centerMaterial.diffuse = 0.3;
    centerMaterial.specular = 0.8;
    centerMaterial.alpha = 0.3;
    centerMaterial.ior = 1.5;

    auto floor = std::make_shared<Plane>(scaling(10, 0.01, 10));
    floor->material = wallMaterial;

    auto center = std::make_shared<Sphere>(translation(-0.5, 1, 0.5));
    center->material = centerMaterial;

    world.objects.push_back(floor);
    world.objects.push_back(center);

    world.lights.emplace_back(Tuple::point(-10, 10, -10), Color(1.0, 1.0, 1.0));

    Camera cam = Camera(1024, 512, M_PI / 3);
    cam.transform(view_transform(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = cam.render(world);
    write_ppm(canvas, "chapter11.ppm");
}
