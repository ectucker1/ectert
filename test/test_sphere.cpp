#include "gtest/gtest.h"
#include "shapes/sphere.h"
#include "math/transform.h"
#include <cmath>

TEST(SphereTest, IntersectingSphere) {
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto sphere = std::make_shared<Sphere>();

    std::vector<Intersection> results = sphere->intersect(ray);
    ASSERT_EQ(results.size(), 2);
    EXPECT_FLOAT_EQ(results[0].t, 4.0);
    EXPECT_FLOAT_EQ(results[1].t, 6.0);
}

TEST(SphereTest, IntersectingSphereTangent) {
    Ray ray = Ray(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1));
    auto sphere = std::make_shared<Sphere>();

    std::vector<Intersection> results = sphere->intersect(ray);
    ASSERT_EQ(results.size(), 2);
    EXPECT_FLOAT_EQ(results[0].t, 5.0);
    EXPECT_FLOAT_EQ(results[1].t, 5.0);
}

TEST(SphereTest, MissingSphere) {
    Ray ray = Ray(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1));
    auto sphere = std::make_shared<Sphere>();

    std::vector<Intersection> results = sphere->intersect(ray);
    ASSERT_EQ(results.size(), 0);
}

TEST(SphereTest, RayInsideSphere) {
    Ray ray = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    auto sphere = std::make_shared<Sphere>();

    std::vector<Intersection> results = sphere->intersect(ray);
    ASSERT_EQ(results.size(), 2);
    EXPECT_FLOAT_EQ(results[0].t, -1.0);
    EXPECT_FLOAT_EQ(results[1].t, 1.0);
}

TEST(SphereTest, RayAfterSphere) {
    Ray ray = Ray(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
    auto sphere = std::make_shared<Sphere>();

    std::vector<Intersection> results = sphere->intersect(ray);
    ASSERT_EQ(results.size(), 2);
    EXPECT_FLOAT_EQ(results[0].t, -6.0);
    EXPECT_FLOAT_EQ(results[1].t, -4.0);
}

TEST(SphereTest, NormalsAxes) {
    auto sphere = std::make_shared<Sphere>();

    EXPECT_EQ(sphere->normal_at(Tuple::point(1, 0, 0)), Tuple::vector(1, 0, 0));
    EXPECT_EQ(sphere->normal_at(Tuple::point(0, 1, 0)), Tuple::vector(0, 1, 0));
    EXPECT_EQ(sphere->normal_at(Tuple::point(0, 0, 1)), Tuple::vector(0, 0, 1));
}

TEST(SphereTest, NormalOffAxis) {
    auto sphere = std::make_shared<Sphere>();

    EXPECT_EQ(sphere->normal_at(Tuple::point(std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3)),
            Tuple::vector(std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3));
}

TEST(SphereTest, NormalIsNormalized) {
    auto sphere = std::make_shared<Sphere>();
    Tuple normal = sphere->normal_at(Tuple::point(std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3));

    EXPECT_EQ(normal, normal.normalized());
}
