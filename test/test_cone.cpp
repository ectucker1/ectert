#include "gtest/gtest.h"
#include "shapes/cone.h"
#include "math/bounds.h"
#include <cmath>

TEST(ConeTest, IntersectingCone) {
    auto shape = std::make_shared<Cone>();

    auto xs = shape->intersect(Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1)));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 5);
    EXPECT_FLOAT_EQ(xs[1].t, 5);
    xs = shape->intersect(Ray(Tuple::point(0, 0, -5), Tuple::vector(1, 1, 1).normalized()));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 8.6602545);
    EXPECT_FLOAT_EQ(xs[1].t, 8.6602545);
    xs = shape->intersect(Ray(Tuple::point(1, 1, -5), Tuple::vector(-0.5, -1, 1).normalized()));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 4.550059);
    EXPECT_FLOAT_EQ(xs[1].t, 49.44994);
}

TEST(ConeTest, IntersectingConeParallelHalves) {
    auto shape = std::make_shared<Cone>();

    auto xs = shape->intersect(Ray(Tuple::point(0, 0, -1), Tuple::vector(0, 1, 1).normalized()));
    ASSERT_EQ(xs.size(), 1);
    EXPECT_FLOAT_EQ(xs[0].t, 0.35355338);
}

TEST(ConeTest, IntersectingConeCaps) {
    auto shape = std::make_shared<Cone>();
    shape->minimum = -0.5;
    shape->maximum = 0.5;
    shape->closed = true;

    auto xs = shape->intersect(Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 1, 0).normalized()));
    EXPECT_EQ(xs.size(), 0);
    xs = shape->intersect(Ray(Tuple::point(0, 0, -0.25), Tuple::vector(0, 1, 1).normalized()));
    EXPECT_EQ(xs.size(), 2);
    xs = shape->intersect(Ray(Tuple::point(0, 0, -0.25), Tuple::vector(0, 1, 0).normalized()));
    EXPECT_EQ(xs.size(), 4);
}

TEST(ConeTest, NormalOnCone) {
    auto shape = std::make_shared<Cone>();

    EXPECT_EQ(shape->normal_at(Tuple::point(1, 1, 1)), Tuple::vector(1, -M_SQRT2, 1).normalized());
    EXPECT_EQ(shape->normal_at(Tuple::point(-1, -1, 0)), Tuple::vector(-1, 1, 0).normalized());
}

TEST(ConeTest, BoundsOfCone) {
    auto c1 = std::make_shared<Cone>();
    auto c2 = std::make_shared<Cone>();
    c2->minimum = -1;
    c2->maximum = 1;

    EXPECT_EQ(c1->bounds(), Bounds(-INFINITY, INFINITY, -INFINITY, INFINITY, -INFINITY, INFINITY));
    EXPECT_EQ(c2->bounds(), Bounds(-1, 1, -1, 1, -1, 1));
}
