#pragma once

#include "world/world.h"
#include "shapes/plane.h"
#include "math/transform.h"
#include "world/camera.h"
#include "files/png.h"
#include "light/lambertian_material.h"
#include "processing/render_process.h"
#include "shapes/sphere.h"
#include "light/gradient_background.h"
#include "light/metal_material.h"
#include "light/dielectric_material.h"
#include "math/rand_util.h"

Color rand_color() {
    return Color(random_float(), random_float(), random_float());
}

Color rand_color(float min, float max) {
    return Color(random_range(min, max), random_range(min, max), random_range(min, max));
}

void run_random_spheres_demo() {
    World world = World();

    auto background = std::make_shared<GradientBackground>(Color(0.5, 0.7, 1.0), Color(1.0, 1.0, 1.0));
    world.background = background;

    auto ground = std::make_shared<Plane>();
    ground->material = std::make_shared<LambertianMaterial>(Color(0.5, 0.5, 0.5));
    world.objects.push_back(ground);

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_float();
            Tuple center = Tuple::point(a + 0.9 * random_float(), 0.2, b + 0.9 * random_float());

            if ((center - Tuple::point(4, 0.2, 0)).magnitude() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.7) {
                    // diffuse
                    auto albedo = rand_color();
                    sphere_material = std::make_shared<LambertianMaterial>(albedo);
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = rand_color(0.5, 1);
                    auto fuzz = random_range(0, 0.5);
                    sphere_material = std::make_shared<MetalMaterial>(albedo, fuzz);
                } else {
                    // glass
                    sphere_material = std::make_shared<DielectricMaterial>(1.5);
                }

                auto sphere = std::make_shared<Sphere>(translation(center.x, center.y, center.z) * scaling(0.2, 0.2, 0.2));
                sphere->material = sphere_material;
                world.objects.push_back(sphere);
            }
        }
    }

    auto back = std::make_shared<Sphere>(translation(4, 1, 0));
    back->material = std::make_shared<LambertianMaterial>(Color(0.4, 0.2, 0.1));
    world.objects.push_back(back);

    auto center = std::make_shared<Sphere>(translation(0, 1, 0));
    center->material = std::make_shared<DielectricMaterial>(1.5);
    world.objects.push_back(center);

    auto front = std::make_shared<Sphere>(translation(-4, 1, 0));
    front->material = std::make_shared<MetalMaterial>(Color(0.7, 0.6, 0.5), 0.0);
    world.objects.push_back(front);

    Camera cam = Camera(1024, 1024, M_PI / 3);
    cam.transform(view_transform(Tuple::point(-8, 2, 3), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    Canvas canvas = RenderProcess(8).render(cam, world, 16);

    write_png(canvas, "random_spheres.png");
}
