#include "world/world.h"
#include "processing/render_process.h"
#include "light/gradient_background.h"
#include "shapes/cube.h"
#include "light/lambertian_material.h"
#include "math/transform.h"
#include "world/camera.h"

std::pair<World, Camera> create_main_render() {
    World world = World();
    world.background = std::make_shared<GradientBackground>(Color(0, 0, 1), Color(1, 1, 1));

    auto sphere = std::make_shared<Cube>();
    sphere->material = std::make_shared<LambertianMaterial>(Color(1, 0, 0));
    world.objects.push_back(sphere);

    Camera cam = Camera(1024, 1024, M_PI / 3);
    cam.transform(view_transform(Tuple::point(-8, 2, 3), Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));

    return {world, cam};
}
