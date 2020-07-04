#include "gtest/gtest.h"
#include "intersection/intersection.h"
#include "intersection/sphere.h"

TEST(IntersectionTest, CreatingIntersection) {
    Sphere s = Sphere();
    Intersection i = Intersection(3.5f, &s);

    EXPECT_FLOAT_EQ(i.t, 3.5f);
    EXPECT_EQ(i.object, &s);
}

TEST(IntersectionTest, CreatingIntersectionList) {
    Sphere s = Sphere();
    Intersection i1 = Intersection(1, &s);
    Intersection i2 = Intersection(2, &s);
    std::vector<Intersection> collection {i1, i2};

    std::vector<Intersection> xs = intersection_list(collection);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t, 1);
    ASSERT_EQ(xs[1].t, 2);
}

TEST(IntersectionTest, AllPositiveHit) {
    Sphere s = Sphere();
    Intersection i1 = Intersection(1, &s);
    Intersection i2 = Intersection(2, &s);
    std::vector<Intersection> collection {i1, i2};
    std::vector<Intersection> xs = intersection_list(collection);

    EXPECT_EQ(hit(xs), i1);
}

TEST(IntersectionTest, SomeNegativeHit) {
    Sphere s = Sphere();
    Intersection i1 = Intersection(-1, &s);
    Intersection i2 = Intersection(1, &s);
    std::vector<Intersection> collection {i1, i2};
    std::vector<Intersection> xs = intersection_list(collection);

    EXPECT_EQ(hit(xs), i2);
}

TEST(IntersectionTest, AllNegativeHit) {
    Sphere s = Sphere();
    Intersection i1 = Intersection(-2, &s);
    Intersection i2 = Intersection(-1, &s);
    std::vector<Intersection> collection {i1, i2};
    std::vector<Intersection> xs = intersection_list(collection);

    EXPECT_EQ(hit(xs), Intersection::NIL);
}

TEST(IntersectionTest, RightOrderHit) {
    Sphere s = Sphere();
    Intersection i1 = Intersection(5, &s);
    Intersection i2 = Intersection(7, &s);
    Intersection i3 = Intersection(-3, &s);
    Intersection i4 = Intersection(2, &s);
    std::vector<Intersection> collection {i1, i2, i3, i4};
    std::vector<Intersection> xs = intersection_list(collection);

    EXPECT_EQ(hit(xs), i4);
}
