#include "gtest/gtest.h"
#include "shapes/triangle.h"
#include "math/bounds.h"

TEST(TriangleTest, ConstructingTriangle) {
    Tuple p1 = Tuple::point(0, 1, 0);
    Tuple p2 = Tuple::point(-1, 0, 0);
    Tuple p3 = Tuple::point(1, 0, 0);

    Triangle tri = Triangle(p1, p2, p3);

    EXPECT_EQ(tri.p1(), p1);
    EXPECT_EQ(tri.p2(), p2);
    EXPECT_EQ(tri.p3(), p3);
    EXPECT_EQ(tri.e1(), Tuple::vector(-1, -1, 0));
    EXPECT_EQ(tri.e2(), Tuple::vector(1, -1, 0));
    EXPECT_EQ(tri.normal(), Tuple::vector(0, 0, -1));
}

TEST(TriangleTest, NormalOnTriangle) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));

    EXPECT_EQ(tri->normal_at(Tuple::point(0, 0.5, 0)), tri->normal());
    EXPECT_EQ(tri->normal_at(Tuple::point(-0.5, 0.75, 0)), tri->normal());
    EXPECT_EQ(tri->normal_at(Tuple::point(0.5, 0.25, 0)), tri->normal());
}

TEST(TriangleTest, IntersectingRayParallelTriangle) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));
    auto ray = Ray(Tuple::point(0, -1, -2), Tuple::vector(0, 1, 0));

    auto xs = tri->intersect(ray);
    EXPECT_TRUE(xs.empty());
}

TEST(TriangeTest, RayMissesP1P3Edge) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));
    auto ray = Ray(Tuple::point(1, 1, -2), Tuple::vector(0, 0, 1));

    auto xs = tri->intersect(ray);
    EXPECT_TRUE(xs.empty());
}

TEST(TriangeTest, RayMissesP1P2Edge) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));
    auto ray = Ray(Tuple::point(-1, 1, -2), Tuple::vector(0, 0, 1));

    auto xs = tri->intersect(ray);
    EXPECT_TRUE(xs.empty());
}

TEST(TriangeTest, RayMissesP2P3Edge) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));
    auto ray = Ray(Tuple::point(0, -1, -2), Tuple::vector(0, 0, 1));

    auto xs = tri->intersect(ray);
    EXPECT_TRUE(xs.empty());
}

TEST(TriangeTest, RayHitsTriangle) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));
    auto ray = Ray(Tuple::point(0, 0.5, -2), Tuple::vector(0, 0, 1));

    auto xs = tri->intersect(ray);
    ASSERT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].t, 2);
}
