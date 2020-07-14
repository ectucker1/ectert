#include "gtest/gtest.h"
#include "shapes/plane.h"

TEST(PlaneTest, NormalConstant) {
    Plane plane = Plane();

    EXPECT_EQ(plane.normal_at(Tuple::point(0, 0, 0)), Tuple::vector(0, 1, 0));
    EXPECT_EQ(plane.normal_at(Tuple::point(10, 0, -10)), Tuple::vector(0, 1, 0));
    EXPECT_EQ(plane.normal_at(Tuple::point(-5, 0, 150)), Tuple::vector(0, 1, 0));
}

TEST(PlaneTest, IntersectParallel) {
    Plane plane = Plane();
    Ray ray = Ray(Tuple::point(0, 10, 0), Tuple::vector(0, 0, 1));

    std::vector<Intersection> xs = plane.intersect(ray);
    EXPECT_EQ(xs.size(), 0);
}

TEST(PlaneTest, IntersectCoplanar) {
    Plane plane = Plane();
    Ray ray = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));

    std::vector<Intersection> xs = plane.intersect(ray);
    EXPECT_EQ(xs.size(), 0);
}

TEST(PlaneTest, IntersectAbove) {
    auto plane = std::make_shared<Plane>();
    Ray ray = Ray(Tuple::point(0, 1, 0), Tuple::vector(0, -1, 0));

    std::vector<Intersection> xs = plane->intersect(ray);
    ASSERT_EQ(xs.size(), 1);
    EXPECT_FLOAT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[0].object, plane);
}

TEST(PlaneTest, IntersectBelow) {
    auto plane = std::make_shared<Plane>();
    Ray ray = Ray(Tuple::point(0, -1, 0), Tuple::vector(0, 1, 0));

    std::vector<Intersection> xs = plane->intersect(ray);
    ASSERT_EQ(xs.size(), 1);
    EXPECT_FLOAT_EQ(xs[0].t, 1);
    EXPECT_EQ(xs[0].object, plane);
}
