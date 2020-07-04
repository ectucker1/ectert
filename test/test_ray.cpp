#include "gtest/gtest.h"
#include "intersection/ray.h"
#include "math/transform.h"

TEST(RayTest, CreatingRay) {
    Tuple origin = Tuple::point(1, 2, 3);
    Tuple direction = Tuple::vector(4, 5, 6);
    Ray ray = Ray(origin, direction);

    EXPECT_EQ(ray.origin, origin);
    EXPECT_EQ(ray.direction, direction);
}

TEST(RayTest, RayTravelDistance) {
    Ray ray = Ray(Tuple::point(2, 3, 4), Tuple::vector(1, 0, 0));

    EXPECT_EQ(ray.position(0), Tuple::point(2, 3, 4));
    EXPECT_EQ(ray.position(1), Tuple::point(3, 3, 4));
    EXPECT_EQ(ray.position(-1), Tuple::point(1, 3, 4));
    EXPECT_EQ(ray.position(2.5), Tuple::point(4.5f, 3, 4));
}

TEST(RayTest, TranslatingRay) {
    Ray ray = Ray(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));
    Matrix matrix = translation(3, 4, 5);
    Ray result = ray.transform(matrix);

    EXPECT_EQ(result.origin, Tuple::point(4, 6, 8));
    EXPECT_EQ(result.direction, Tuple::vector(0, 1, 0));
}

TEST(RayTest, ScalingRay) {
    Ray ray = Ray(Tuple::point(1, 2, 3), Tuple::vector(0, 1, 0));
    Matrix matrix = scaling(2, 3, 4);
    Ray result = ray.transform(matrix);

    EXPECT_EQ(result.origin, Tuple::point(2, 6, 12));
    EXPECT_EQ(result.direction, Tuple::vector(0, 3, 0));
}
