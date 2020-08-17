#include "gtest/gtest.h"
#include "intersection/intersection.h"
#include "shapes/sphere.h"
#include "shapes/plane.h"
#include "intersection/hit.h"
#include "math/transform.h"
#include "test_helpers.h"
#include <cmath>

TEST(IntersectionTest, CreatingIntersection) {
    auto s = std::make_shared<Sphere>();
    Intersection i = Intersection(3.5f, s);

    EXPECT_FLOAT_EQ(i.t, 3.5f);
    EXPECT_EQ(i.object, s);
}

TEST(IntersectionTest, CreatingIntersectionList) {
    auto s = std::make_shared<Sphere>();
    Intersection i1 = Intersection(1, s);
    Intersection i2 = Intersection(2, s);
    std::vector<Intersection> collection {i1, i2};

    std::vector<Intersection> xs = sort_intersections(collection);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t, 1);
    ASSERT_EQ(xs[1].t, 2);
}

TEST(IntersectionTest, AllPositiveHit) {
    auto s = std::make_shared<Sphere>();
    Intersection i1 = Intersection(1, s);
    Intersection i2 = Intersection(2, s);
    std::vector<Intersection> collection {i1, i2};
    std::vector<Intersection> xs = sort_intersections(collection);

    EXPECT_EQ(hit(xs), i1);
}

TEST(IntersectionTest, SomeNegativeHit) {
    auto s = std::make_shared<Sphere>();
    Intersection i1 = Intersection(-1, s);
    Intersection i2 = Intersection(1, s);
    std::vector<Intersection> collection {i1, i2};
    std::vector<Intersection> xs = sort_intersections(collection);

    EXPECT_EQ(hit(xs), i2);
}

TEST(IntersectionTest, AllNegativeHit) {
    auto s = std::make_shared<Sphere>();
    Intersection i1 = Intersection(-2, s);
    Intersection i2 = Intersection(-1, s);
    std::vector<Intersection> collection {i1, i2};
    std::vector<Intersection> xs = sort_intersections(collection);

    EXPECT_EQ(hit(xs), Intersection::NIL);
}

TEST(IntersectionTest, RightOrderHit) {
    auto s = std::make_shared<Sphere>();
    Intersection i1 = Intersection(5, s);
    Intersection i2 = Intersection(7, s);
    Intersection i3 = Intersection(-3, s);
    Intersection i4 = Intersection(2, s);
    std::vector<Intersection> collection {i1, i2, i3, i4};
    std::vector<Intersection> xs = sort_intersections(collection);

    EXPECT_EQ(hit(xs), i4);
}

TEST(IntersectionTest, PrecomputeHitDataOutside) {
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto shape = std::make_shared<Sphere>();
    Intersection x = Intersection(4, shape);

    Hit hit = Hit(x, ray, std::vector<Intersection>());
    EXPECT_EQ(hit.t, x.t);
    EXPECT_EQ(hit.object, shape);
    EXPECT_EQ(hit.point, Tuple::point(0, 0, -1));
    EXPECT_EQ(hit.eyev, Tuple::vector(0, 0, -1));
    EXPECT_EQ(hit.normalv, Tuple::vector(0, 0, -1));
    EXPECT_FALSE(hit.inside);
}

TEST(IntersectionTest, PrecomputeHitDataInside) {
    Ray ray = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    auto shape = std::make_shared<Sphere>();
    Intersection x = Intersection(1, shape);

    Hit hit = Hit(x, ray, std::vector<Intersection>());
    EXPECT_EQ(hit.t, x.t);
    EXPECT_EQ(hit.object, shape);
    EXPECT_EQ(hit.point, Tuple::point(0, 0, 1));
    EXPECT_EQ(hit.eyev, Tuple::vector(0, 0, -1));
    EXPECT_EQ(hit.normalv, Tuple::vector(0, 0, -1));
    EXPECT_TRUE(hit.inside);
}

TEST(IntersectionTest, HitOffsetPoint) {
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto s = std::make_shared<Sphere>(translation(0, 0, 1));
    std::vector<Intersection> xs = s->intersect(ray);
    Intersection x = hit(xs);

    Hit hit = Hit(x, ray, std::vector<Intersection>());
    EXPECT_LT(hit.over_point.z, -0.01 / 2);
    EXPECT_GT(hit.point.z, hit.over_point.z);
}

TEST(IntersectionTest, HitComputeReflection) {
    Ray ray = Ray(Tuple::point(0, 1, -1), Tuple::vector(0, -M_SQRT2 / 2, M_SQRT2 / 2));
    auto shape = std::make_shared<Plane>();
    std::vector<Intersection> xs = shape->intersect(ray);
    Intersection x = hit(xs);

    Hit hit = Hit(x, ray, std::vector<Intersection>());
    EXPECT_EQ(hit.reflectv, Tuple::vector(0, M_SQRT2 / 2, M_SQRT2 / 2));
}

TEST(IntersectionTest, FindingMaterialN1N2) {
    auto a = test_glass_sphere();
    a->transform(scaling(2, 2, 2));
    a->material.ior = 1.5;

    auto b = test_glass_sphere();
    b->transform(translation(0, 0, -0.25));
    b->material.ior = 2.0;

    auto c = test_glass_sphere();
    c->transform(translation(0, 0, 0.25));
    c->material.ior = 2.5;

    Ray ray = Ray(Tuple::point(0, 0, -4), Tuple::vector(0, 0, 1));
    auto xs = std::vector<Intersection>();
    xs.emplace_back(2, a);
    xs.emplace_back(2.75, b);
    xs.emplace_back(3.25, c);
    xs.emplace_back(4.75, b);
    xs.emplace_back(5.25, c);
    xs.emplace_back(6, a);

    Hit hit0 = Hit(xs[0], ray, xs);
    EXPECT_FLOAT_EQ(hit0.n1, 1.0);
    EXPECT_FLOAT_EQ(hit0.n2, 1.5);
    Hit hit1 = Hit(xs[1], ray, xs);
    EXPECT_FLOAT_EQ(hit1.n1, 1.5);
    EXPECT_FLOAT_EQ(hit1.n2, 2.0);
    Hit hit2 = Hit(xs[2], ray, xs);
    EXPECT_FLOAT_EQ(hit2.n1, 2.0);
    EXPECT_FLOAT_EQ(hit2.n2, 2.5);
    Hit hit3 = Hit(xs[3], ray, xs);
    EXPECT_FLOAT_EQ(hit3.n1, 2.5);
    EXPECT_FLOAT_EQ(hit3.n2, 2.5);
    Hit hit4 = Hit(xs[4], ray, xs);
    EXPECT_FLOAT_EQ(hit4.n1, 2.5);
    EXPECT_FLOAT_EQ(hit4.n2, 1.5);
    Hit hit5 = Hit(xs[5], ray, xs);
    EXPECT_FLOAT_EQ(hit5.n1, 1.5);
    EXPECT_FLOAT_EQ(hit5.n2, 1.0);
}

TEST(IntersectionTest, UnderPointUnderSurface) {
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto shape = test_glass_sphere();
    shape->transform(translation(0, 0, 1));
    Intersection x = Intersection(5, shape);
    auto xs = std::vector<Intersection>();
    xs.push_back(x);

    Hit hit = Hit(x, ray, xs);
    // Hit should be shifted upwards
    EXPECT_GT(hit.under_point.z, 0.01 / 2);
    EXPECT_LT(hit.point.z, hit.under_point.z);
}

TEST(IntersectionTest, SchlickTotalInternal) {
    auto shape = test_glass_sphere();
    Ray ray = Ray(Tuple::point(0, 0, M_SQRT2 / 2), Tuple::vector(0, 1, 0));
    auto xs = std::vector<Intersection>();
    xs.emplace_back(-M_SQRT2 / 2, shape);
    xs.emplace_back(M_SQRT2 / 2, shape);

    Hit hit = Hit(xs[1], ray, xs);
    EXPECT_FLOAT_EQ(hit.schlick_reflectance(), 1.0);
}

TEST(IntersectionTest, SchlickSmallPerpendicular) {
    auto shape = test_glass_sphere();
    Ray ray = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 1, 0));
    auto xs = std::vector<Intersection>();
    xs.emplace_back(-1, shape);
    xs.emplace_back(1, shape);

    Hit hit = Hit(xs[1], ray, xs);
    EXPECT_FLOAT_EQ(hit.schlick_reflectance(), 0.04);
}

TEST(IntersectionTest, SchlickSmallShallow) {
    auto shape = test_glass_sphere();
    Ray ray = Ray(Tuple::point(0, 0.99, -2), Tuple::vector(0, 0, 1));
    auto xs = std::vector<Intersection>();
    xs.emplace_back(1.8589, shape);

    Hit hit = Hit(xs[0], ray, xs);
    EXPECT_FLOAT_EQ(hit.schlick_reflectance(), 0.4887307);
}

TEST(IntersectionTest, StoringUV) {
    Intersection x = Intersection(0, nullptr, 0.2, 0.4);

    EXPECT_FLOAT_EQ(x.u, 0.2);
    EXPECT_FLOAT_EQ(x.v, 0.4);
}
