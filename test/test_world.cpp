#include "gtest/gtest.h"
#include "world/world.h"
#include "math/transform.h"
#include "shapes/plane.h"
#include "shapes/sphere.h"
#include "pattern/test_pattern.h"
#include "light/lambertian_material.h"
#include "light/metal_material.h"
#include "light/dielectric_material.h"
#include <algorithm>
#include <cmath>

TEST(WorldTest, CreatingWorld) {
    World world = World();

    EXPECT_EQ(world.objects.size(), 0);
}

TEST(WorldTest, ExampleWorld) {
    World world = World::example_world();
    EXPECT_EQ(world.objects.size(), 2);
}

TEST(WorldTest, IntersectWorld) {
    World world = World::example_world();
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

    std::vector<Intersection> xs = world.intersect(ray);
    ASSERT_EQ(xs.size(), 4);
    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_FLOAT_EQ(xs[1].t, 4.5);
    EXPECT_FLOAT_EQ(xs[2].t, 5.5);
    EXPECT_FLOAT_EQ(xs[3].t, 6);
}

TEST(WorldTest, ColorMiss) {
    World world = World::example_world();
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 1, 0));

    EXPECT_EQ(world.color_at(ray, 0), Color(1, 1, 1));
}

TEST(WorldTest, ColorHit) {
    World world = World::example_world();
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

    EXPECT_EQ(world.color_at(ray, 1), Color(0.8, 1, 0.6));
}

TEST(WorldTest, RepeatedReflectionTerminates) {
    World world = World();
    auto lower = std::make_shared<Plane>(translation(0, -1, 0));
    lower->material = std::make_shared<MetalMaterial>();
    world.objects.push_back(lower);
    auto upper = std::make_shared<Plane>(translation(0, 1, 0));
    upper->material = std::make_shared<MetalMaterial>();
    world.objects.push_back(upper);
    Ray ray = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));

    Color color = world.color_at(ray, 5);
    SUCCEED();
}

TEST(WorldTest, ReflectedColorMaxRecursion) {
    World world = World::example_world();
    auto shape = std::make_shared<Plane>(translation(0, -1, 0));
    shape->material = std::make_shared<MetalMaterial>();
    world.objects.push_back(shape);
    Ray ray = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -M_SQRT2 / 2, M_SQRT2 / 2));
    Intersection x = Intersection(M_SQRT2, shape);
    Hit hit = Hit(x, ray);

    EXPECT_EQ(world.shade_hit(hit, 0), Color(0, 0, 0));
}

TEST(WorldTest, ShadeHitTransparent) {
    World world = World::example_world();
    auto floor = std::make_shared<Plane>(translation(0, -1, 0));
    floor->material = std::make_shared<DielectricMaterial>(1.5);
    world.objects.push_back(floor);
    auto ball = std::make_shared<Sphere>(translation(0, -3.5, -0.5));
    ball->material = std::make_shared<LambertianMaterial>(Color(1, 0, 0));
    world.objects.push_back(ball);
    Ray ray = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -M_SQRT2 / 2, M_SQRT2 / 2));
    auto xs = std::vector<Intersection>();
    xs.emplace_back(M_SQRT2, floor);
    Hit hit = Hit(xs[0], ray, xs);

    EXPECT_EQ(world.shade_hit(hit, 5), Color(0.8, 0, 0));
}
