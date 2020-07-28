#include "gtest/gtest.h"
#include "world/world.h"
#include "math/transform.h"
#include "shapes/plane.h"
#include "pattern/test_pattern.h"
#include <algorithm>
#include <cmath>

TEST(WorldTest, CreatingWorld) {
    World world = World();

    EXPECT_EQ(world.objects.size(), 0);
    EXPECT_EQ(world.lights.size(), 0);
}

TEST(WorldTest, ExampleWorld) {
    PointLight light = PointLight(Tuple::point(-10, 10, -10), Color(1, 1, 1));
    Sphere s1 = Sphere();
    s1.material.color = Color(0.8, 1.0, 0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;
    Sphere s2 = Sphere(scaling(0.5, 0.5, 0.5));

    World world = World::example_world();
    EXPECT_EQ(world.lights.front(), light);
    EXPECT_EQ(world.objects.size(), 2);
    //EXPECT_NE(std::find(world.objects.begin(), world.objects.end(), &s1), world.objects.end());
    //EXPECT_NE(std::find(world.objects.begin(), world.objects.end(), &s2), world.objects.end());
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

    EXPECT_EQ(world.color_at(ray, 0), Color(0, 0, 0));
}

TEST(WorldTest, ColorHit) {
    World world = World::example_world();
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

    EXPECT_EQ(world.color_at(ray, 0), Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ColorBehind) {
    World world = World::example_world();
    world.objects[0]->material.ambient = 1;
    world.objects[1]->material.ambient = 1;
    Ray ray = Ray(Tuple::point(0, 0, 0.75), Tuple::vector(0, 0, -1));

    EXPECT_EQ(world.color_at(ray, 0), world.objects[1]->material.color);
}

TEST(WorldTest, NoShadowNothingCollinear) {
    World world = World::example_world();
    Tuple point = Tuple::point(0, 10, 0);

    EXPECT_FALSE(world.is_shadowed(point, world.lights.front()));
}

TEST(WorldTest, ShadowObjectBetween) {
    World world = World::example_world();
    Tuple point = Tuple::point(10, -10, 10);

    EXPECT_TRUE(world.is_shadowed(point, world.lights.front()));
}

TEST(WorldTest, NoShadowObjectBehindLight) {
    World world = World::example_world();
    Tuple point = Tuple::point(-20, 20, -20);

    EXPECT_FALSE(world.is_shadowed(point, world.lights.front()));
}

TEST(WorldTest, NoShadowObjectBehindPoint) {
    World world = World::example_world();
    Tuple point = Tuple::point(-2, 2, -2);

    EXPECT_FALSE(world.is_shadowed(point, world.lights.front()));
}

TEST(WorldTest, ShadeHitInShadow) {
    World world = World();
    world.lights.emplace_back(Tuple::point(0, 0, -10), Color(1, 1, 1));
    auto s1 = std::make_shared<Sphere>();
    world.objects.push_back(s1);
    auto s2 = std::make_shared<Sphere>(translation(0, 0, 10));
    world.objects.push_back(s2);
    Ray ray = Ray(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
    Intersection x = Intersection(4, s2);
    Hit hit = Hit(x, ray);

    Color color = world.shade_hit(hit, 0);
    EXPECT_EQ(color, Color(0.1, 0.1, 0.1));
}

TEST(WorldTest, ReflectedColorNonreflective) {
    World world = World::example_world();
    Ray ray = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    auto shape = world.objects[1];
    shape->material.ambient = 1.0;
    Intersection x = Intersection(1, shape);
    Hit hit = Hit(x, ray);

    EXPECT_EQ(world.reflected_color(hit, 1), Color(0, 0, 0));
}

TEST(WorldTest, ReflectedColorReflective) {
    World world = World::example_world();
    auto shape = std::make_shared<Plane>(translation(0, -1, 0));
    shape->material.reflectivity = 0.5;
    world.objects.push_back(shape);
    Ray ray = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -M_SQRT2 / 2, M_SQRT2 / 2));
    Intersection x = Intersection(M_SQRT2, shape);
    Hit hit = Hit(x, ray);

    EXPECT_EQ(world.reflected_color(hit, 1), Color(0.19032, 0.2379, 0.14274));
}

TEST(WorldTest, ShadeHitReflective) {
    World world = World::example_world();
    auto shape = std::make_shared<Plane>(translation(0, -1, 0));
    shape->material.reflectivity = 0.5;
    world.objects.push_back(shape);
    Ray ray = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -M_SQRT2 / 2, M_SQRT2 / 2));
    Intersection x = Intersection(M_SQRT2, shape);
    Hit hit = Hit(x, ray);

    EXPECT_EQ(world.shade_hit(hit, 1), Color(0.87677, 0.92436, 0.82918));
}

TEST(WorldTest, RepeatedReflectionTerminates) {
    World world = World();
    world.lights.emplace_back(Tuple::point(0, 0, 0), Color(1, 1, 1));
    auto lower = std::make_shared<Plane>(translation(0, -1, 0));
    lower->material.reflectivity = 1.0;
    world.objects.push_back(lower);
    auto upper = std::make_shared<Plane>(translation(0, 1, 0));
    upper->material.reflectivity = 1.0;
    world.objects.push_back(upper);
    Ray ray = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));

    Color color = world.color_at(ray, 5);
    SUCCEED();
}

TEST(WorldTest, ReflectedColorMaxRecursion) {
    World world = World::example_world();
    auto shape = std::make_shared<Plane>(translation(0, -1, 0));
    shape->material.reflectivity = 0.5;
    world.objects.push_back(shape);
    Ray ray = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -M_SQRT2 / 2, M_SQRT2 / 2));
    Intersection x = Intersection(M_SQRT2, shape);
    Hit hit = Hit(x, ray);

    EXPECT_EQ(world.reflected_color(hit, 0), Color(0, 0, 0));
}

TEST(WorldTest, RefractedColorOpaque) {
    World world = World::example_world();
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto shape = world.objects[0];
    auto xs = std::vector<Intersection>();
    xs.emplace_back(4, shape);
    xs.emplace_back(6, shape);
    Hit hit = Hit(xs[0], ray, xs);

    EXPECT_EQ(world.refracted_color(hit, 1), Color(0, 0, 0));
}

TEST(WorldTest, RefractedColorMaxRecursiveDepth) {
    World world = World::example_world();
    world.objects[0]->material.alpha = 0.0;
    world.objects[0]->material.ior = 1.5;
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto shape = world.objects[0];
    auto xs = std::vector<Intersection>();
    xs.emplace_back(4, shape);
    xs.emplace_back(6, shape);
    Hit hit = Hit(xs[0], ray, xs);

    EXPECT_EQ(world.refracted_color(hit, 0), Color(0, 0, 0));
}

TEST(WorldTest, RefractedColorTotalInternalRefraction) {
    World world = World::example_world();
    world.objects[0]->material.alpha = 0.0;
    world.objects[0]->material.ior = 1.5;
    Ray ray = Ray(Tuple::point(0, 0, M_SQRT2 / 2), Tuple::vector(0, 1, 0));
    auto xs = std::vector<Intersection>();
    xs.emplace_back(-M_SQRT2 / 2, world.objects[0]);
    xs.emplace_back(M_SQRT2 / 2, world.objects[0]);
    Hit hit = Hit(xs[1], ray, xs);

    EXPECT_EQ(world.refracted_color(hit, 5), Color(0, 0, 0));
}

TEST(WorldTest, RefractedColorRefractedRay) {
    World world = World::example_world();
    world.objects[0]->material.ambient = 1.0;
    world.objects[0]->material.pattern = std::make_shared<TestPattern>();
    world.objects[1]->material.alpha = 0.0;
    world.objects[1]->material.ior = 1.5;
    Ray ray = Ray(Tuple::point(0, 0, 0.1), Tuple::vector(0, 1, 0));
    auto xs = std::vector<Intersection>();
    xs.emplace_back(-0.9899, world.objects[0]);
    xs.emplace_back(-0.4899, world.objects[1]);
    xs.emplace_back(0.4899, world.objects[1]);
    xs.emplace_back(0.9899, world.objects[0]);
    Hit hit = Hit(xs[2], ray, xs);

    EXPECT_EQ(world.refracted_color(hit, 5), Color(0, 0.99888, 0.04725));
}

TEST(WorldTest, ShadeHitTransparent) {
    World world = World::example_world();
    auto floor = std::make_shared<Plane>(translation(0, -1, 0));
    floor->material.alpha = 0.5;
    floor->material.ior = 1.5;
    world.objects.push_back(floor);
    auto ball = std::make_shared<Sphere>(translation(0, -3.5, -0.5));
    ball->material.color = Color(1, 0, 0);
    ball->material.ambient = 0.5;
    world.objects.push_back(ball);
    Ray ray = Ray(Tuple::point(0, 0, -3), Tuple::vector(0, -M_SQRT2 / 2, M_SQRT2 / 2));
    auto xs = std::vector<Intersection>();
    xs.emplace_back(M_SQRT2, floor);
    Hit hit = Hit(xs[0], ray, xs);

    EXPECT_EQ(world.shade_hit(hit, 5), Color(0.93642, 0.68642, 0.68642));
}
