#include "gtest/gtest.h"
#include "shapes/cube.h"
#include "math/bounds.h"

TEST(CubeTest, IntersectingCube) {
    auto c = std::make_shared<Cube>();

    auto xs = c->intersect(Ray(Tuple::point(5, 0.5, 0), Tuple::vector(-1, 0, 0)));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_FLOAT_EQ(xs[1].t, 6);
    xs = c->intersect(Ray(Tuple::point(-5, 0.5, 0), Tuple::vector(1, 0, 0)));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_FLOAT_EQ(xs[1].t, 6);
    xs = c->intersect(Ray(Tuple::point(0.5, 5, 0), Tuple::vector(0, -1, 0)));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_FLOAT_EQ(xs[1].t, 6);
    xs = c->intersect(Ray(Tuple::point(0.5, -5, 0), Tuple::vector(0, 1, 0)));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_FLOAT_EQ(xs[1].t, 6);
    xs = c->intersect(Ray(Tuple::point(0.5, 0, 5), Tuple::vector(0, 0, -1)));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_FLOAT_EQ(xs[1].t, 6);
    xs = c->intersect(Ray(Tuple::point(0.5, 0, -5), Tuple::vector(0, 0, 1)));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_FLOAT_EQ(xs[1].t, 6);
    xs = c->intersect(Ray(Tuple::point(0, 0.5, 0), Tuple::vector(0, 0, 1)));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, -1);
    EXPECT_FLOAT_EQ(xs[1].t, 1);
}

TEST(CubeTest, MissingCube) {
    auto c = std::make_shared<Cube>();

    auto xs = c->intersect(Ray(Tuple::point(-2, 0, 0), Tuple::vector(0.2673, 0.5345, 0.8018)));
    ASSERT_EQ(xs.size(), 0);
    xs = c->intersect(Ray(Tuple::point(0, -2, 0), Tuple::vector(0.8018, 0.2673, 0.5345)));
    ASSERT_EQ(xs.size(), 0);
    xs = c->intersect(Ray(Tuple::point(0, 0, -2), Tuple::vector(0.5345, 0.8018, 0.2673)));
    ASSERT_EQ(xs.size(), 0);
    xs = c->intersect(Ray(Tuple::point(2, 0, 2), Tuple::vector(0, 0, -1)));
    ASSERT_EQ(xs.size(), 0);
    xs = c->intersect(Ray(Tuple::point(0, 2, 2), Tuple::vector(0, -1, 0)));
    ASSERT_EQ(xs.size(), 0);
    xs = c->intersect(Ray(Tuple::point(2, 2, 0), Tuple::vector(-1, 0, 0)));
    ASSERT_EQ(xs.size(), 0);
}

TEST(CubeTest, NormalOnCube) {
    auto c = std::make_shared<Cube>();

    EXPECT_EQ(c->normal_at(Tuple::point(1, 0.5, -0.8)), Tuple::vector(1, 0, 0));
    EXPECT_EQ(c->normal_at(Tuple::point(-1, -0.2, 0.9)), Tuple::vector(-1, 0, 0));
    EXPECT_EQ(c->normal_at(Tuple::point(-0.4, 1, -0.1)), Tuple::vector(0, 1, 0));
    EXPECT_EQ(c->normal_at(Tuple::point(0.3, -1, -0.7)), Tuple::vector(0, -1, 0));
    EXPECT_EQ(c->normal_at(Tuple::point(-0.6, 0.3, 1)), Tuple::vector(0, 0, 1));
    EXPECT_EQ(c->normal_at(Tuple::point(0.4, 0.4, -1)), Tuple::vector(0, 0, -1));
    EXPECT_EQ(c->normal_at(Tuple::point(1, 1, 1)), Tuple::vector(1, 0, 0));
    EXPECT_EQ(c->normal_at(Tuple::point(-1, -1, -1)), Tuple::vector(-1, 0, 0));
}

TEST(CubeTest, BoundsOfCube) {
    auto cube = std::make_shared<Cube>();

    EXPECT_EQ(cube->bounds(), Bounds(-1, 1, -1, 1, -1, 1));
}
