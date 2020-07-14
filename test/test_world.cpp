#include "gtest/gtest.h"
#include "world/world.h"
#include "math/transform.h"
#include <algorithm>

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

    EXPECT_EQ(world.color_at(ray), Color(0, 0, 0));
}

TEST(WorldTest, ColorHit) {
    World world = World::example_world();
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

    EXPECT_EQ(world.color_at(ray), Color(0.38066, 0.47583, 0.2855));
}

TEST(WorldTest, ColorBehind) {
    World world = World::example_world();
    world.objects[0]->material.ambient = 1;
    world.objects[1]->material.ambient = 1;
    Ray ray = Ray(Tuple::point(0, 0, 0.75), Tuple::vector(0, 0, -1));

    EXPECT_EQ(world.color_at(ray), world.objects[1]->material.color);
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

    Color color = world.shade_hit(hit);
    EXPECT_EQ(color, Color(0.1, 0.1, 0.1));
}
