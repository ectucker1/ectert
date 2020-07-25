#include "gtest/gtest.h"
#include "intersection/intersection.h"
#include "shapes/sphere.h"
#include "shapes/plane.h"
#include "intersection/hit.h"
#include "math/transform.h"
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

    Hit hit = Hit(x, ray);
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

    Hit hit = Hit(x, ray);
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

    Hit hit = Hit(x, ray);
    EXPECT_LT(hit.over_point.z, -0.01 / 2);
    EXPECT_GT(hit.point.z, hit.over_point.z);
}

TEST(IntersectionTest, HitComputeReflection) {
    Ray ray = Ray(Tuple::point(0, 1, -1), Tuple::vector(0, -M_SQRT2 / 2, M_SQRT2 / 2));
    auto shape = std::make_shared<Plane>();
    std::vector<Intersection> xs = shape->intersect(ray);
    Intersection x = hit(xs);

    Hit hit = Hit(x, ray);
    EXPECT_EQ(hit.reflectv, Tuple::vector(0, M_SQRT2 / 2, M_SQRT2 / 2));
}
