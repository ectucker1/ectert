#include "gtest/gtest.h"
#include "shapes/cylinder.h"
#include "math/bounds.h"
#include <cmath>

TEST(CylinderTest, MissingCylinder) {
    auto cylinder = std::make_shared<Cylinder>();

    auto xs = cylinder->intersect(Ray(Tuple::point(1, 0, 0), Tuple::vector(0, 1, 0)));
    EXPECT_EQ(xs.size(), 0);
    xs = cylinder->intersect(Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0)));
    EXPECT_EQ(xs.size(), 0);
    xs = cylinder->intersect(Ray(Tuple::point(0, 0, -5), Tuple::vector(1, 1, 1)));
    EXPECT_EQ(xs.size(), 0);
}

TEST(CylinderTest, IntersectingCylinder) {
    auto cylinder = std::make_shared<Cylinder>();

    auto xs = cylinder->intersect(Ray(Tuple::point(1, 0, -5), Tuple::vector(0, 0, 1)));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 5);
    EXPECT_FLOAT_EQ(xs[1].t, 5);
    xs = cylinder->intersect(Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1)));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 4);
    EXPECT_FLOAT_EQ(xs[1].t, 6);
    xs = cylinder->intersect(Ray(Tuple::point(0.5, 0, -5), Tuple::vector(0.1, 1, 1).normalized()));
    ASSERT_EQ(xs.size(), 2);
    EXPECT_FLOAT_EQ(xs[0].t, 6.8080058);
    EXPECT_FLOAT_EQ(xs[1].t, 7.0886984);
}

TEST(CylinderTest, NormalOnCylinder) {
    auto cylinder = std::make_shared<Cylinder>();

    EXPECT_EQ(cylinder->normal_at(Tuple::point(1, 0, 0)), Tuple::vector(1, 0, 0));
    EXPECT_EQ(cylinder->normal_at(Tuple::point(0, 5, -1)), Tuple::vector(0, 0, -1));
    EXPECT_EQ(cylinder->normal_at(Tuple::point(0, -2, 1)), Tuple::vector(0, 0, 1));
    EXPECT_EQ(cylinder->normal_at(Tuple::point(-1, 1, 0)), Tuple::vector(-1, 0, 0));
}

TEST(CylinderTest, CylinderDefaultMinMaxClosed) {
    auto cylinder = std::make_shared<Cylinder>();

    EXPECT_EQ(cylinder->minimum, -INFINITY);
    EXPECT_EQ(cylinder->maximum, INFINITY);
    EXPECT_EQ(cylinder->closed, false);
}

TEST(CylinderTest, IntersectingConstrainedCylinder) {
    auto cylinder = std::make_shared<Cylinder>();
    cylinder->minimum = 1;
    cylinder->maximum = 2;

    auto xs = cylinder->intersect(Ray(Tuple::point(0, 1.5, 0), Tuple::vector(0.1, 1, 0).normalized()));
    EXPECT_EQ(xs.size(), 0);
    xs = cylinder->intersect(Ray(Tuple::point(0, 3, -5), Tuple::vector(0, 0, 1)));
    EXPECT_EQ(xs.size(), 0);
    xs = cylinder->intersect(Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1)));
    EXPECT_EQ(xs.size(), 0);
    xs = cylinder->intersect(Ray(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1)));
    EXPECT_EQ(xs.size(), 0);
    xs = cylinder->intersect(Ray(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1)));
    EXPECT_EQ(xs.size(), 0);
    xs = cylinder->intersect(Ray(Tuple::point(0, 1.5, -2), Tuple::vector(0, 0, 1)));
    EXPECT_EQ(xs.size(), 2);
}

TEST(CylinderTest, IntersectingCaps) {
    auto cylinder = std::make_shared<Cylinder>();
    cylinder->minimum = 1;
    cylinder->maximum = 2;
    cylinder->closed = true;

    auto xs = cylinder->intersect(Ray(Tuple::point(0, 3, 0), Tuple::vector(0, -1, 0).normalized()));
    EXPECT_EQ(xs.size(), 2);
    xs = cylinder->intersect(Ray(Tuple::point(0, 3, -2), Tuple::vector(0, -1, 2).normalized()));
    EXPECT_EQ(xs.size(), 2);
    xs = cylinder->intersect(Ray(Tuple::point(0, 4, -2), Tuple::vector(0, -1, 1).normalized()));
    EXPECT_EQ(xs.size(), 2);
    xs = cylinder->intersect(Ray(Tuple::point(0, 0, -2), Tuple::vector(0, 1, 2).normalized()));
    EXPECT_EQ(xs.size(), 2);
    xs = cylinder->intersect(Ray(Tuple::point(0, -1, -2), Tuple::vector(0, 1, 1).normalized()));
    EXPECT_EQ(xs.size(), 2);
}

TEST(CylinderTest, NormalOnCaps) {
    auto cylinder = std::make_shared<Cylinder>();
    cylinder->minimum = 1;
    cylinder->maximum = 2;
    cylinder->closed = true;

    EXPECT_EQ(cylinder->normal_at(Tuple::point(0, 1, 0)), Tuple::vector(0, -1, 0));
    EXPECT_EQ(cylinder->normal_at(Tuple::point(0.5, 1, 0)), Tuple::vector(0, -1, 0));
    EXPECT_EQ(cylinder->normal_at(Tuple::point(0, 1, 0.5)), Tuple::vector(0, -1, 0));
    EXPECT_EQ(cylinder->normal_at(Tuple::point(0, 2, 0)), Tuple::vector(0, 1, 0));
    EXPECT_EQ(cylinder->normal_at(Tuple::point(0.5, 2, 0)), Tuple::vector(0, 1, 0));
    EXPECT_EQ(cylinder->normal_at(Tuple::point(0, 2, 0.5)), Tuple::vector(0, 1, 0));
}

TEST(CylinderTest, BoundsOfCylinder) {
    auto c1 = std::make_shared<Cylinder>();
    auto c2 = std::make_shared<Cylinder>();
    c2->minimum = -1;
    c2->maximum = 1;

    EXPECT_EQ(c1->bounds(), Bounds(-1, 1, -INFINITY, INFINITY, -1, 1));
    EXPECT_EQ(c2->bounds(), Bounds(-1, 1, -1, 1, -1, 1));
}
