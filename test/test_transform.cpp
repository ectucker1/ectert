#include "gtest/gtest.h"
#include "math/transform.h"
#include <cmath>

TEST(TransformTest, MultiplyingTranslationPoint) {
    Matrix transform = translation(5, -3, 2);
    Tuple point = Tuple::point(-3, 4, 5);

    EXPECT_EQ(transform * point, Tuple::point(2, 1, 7));
}

TEST(TransformTest, MultiplyingInverseTranslationPoint) {
    Matrix transform = translation(5, -3, 2);
    Tuple point = Tuple::point(-3, 4, 5);

    EXPECT_EQ(transform.inverse() * point, Tuple::point(-8, 7, 3));
}

TEST(TransformTest, MultiplyingTranslationVector) {
    Matrix transform = translation(5, -3, 2);
    Tuple vector = Tuple::vector(-3, 4, 5);

    EXPECT_EQ(transform * vector, vector);
}

TEST(TransformTest, ScalingPoint) {
    Matrix transform = scaling(2, 3, 4);
    Tuple point = Tuple::point(-4, 6, 8);

    EXPECT_EQ(transform * point, Tuple::point(-8, 18, 32));
}

TEST(TransformTest, ScalingVector) {
    Matrix transform = scaling(2, 3, 4);
    Tuple vector = Tuple::vector(-4, 6, 8);

    EXPECT_EQ(transform * vector, Tuple::vector(-8, 18, 32));
}

TEST(TransformTest, ScalingInverseVector) {
    Matrix transform = scaling(2, 3, 4);
    Tuple vector = Tuple::vector(-4, 6, 8);

    EXPECT_EQ(transform.inverse() * vector, Tuple::vector(-2, 2, 2));
}

TEST(TransformTest, ScalingReflection) {
    Matrix transform = scaling(-1, 1, 1);
    Tuple point = Tuple::point(2, 3, 4);

    EXPECT_EQ(transform * point, Tuple::point(-2, 3, 4));
}

TEST(TransformTest, RotatingX) {
    Matrix halfQuarter = rotation_x(M_PI_4);
    Matrix fullQuarter = rotation_x(M_PI_2);
    Tuple point = Tuple::point(0, 1, 0);

    EXPECT_EQ(halfQuarter * point, Tuple::point(0, M_SQRT2 / 2, M_SQRT2 / 2));
    EXPECT_EQ(fullQuarter * point, Tuple::point(0, 0, 1));
}

TEST(TransformTest, RotatingInverseX) {
    Matrix halfQuarter = rotation_x(M_PI_4);
    Tuple point = Tuple::point(0, 1, 0);

    EXPECT_EQ(halfQuarter.inverse() * point, Tuple::point(0, M_SQRT2 / 2, -M_SQRT2 / 2));
}

TEST(TransformTest, RotatingY) {
    Matrix halfQuarter = rotation_y(M_PI_4);
    Matrix fullQuarter = rotation_y(M_PI_2);
    Tuple point = Tuple::point(0, 0, 1);

    EXPECT_EQ(halfQuarter * point, Tuple::point(M_SQRT2 / 2, 0, M_SQRT2 / 2));
    EXPECT_EQ(fullQuarter * point, Tuple::point(1, 0, 0));
}

TEST(TransformTest, RotatingZ) {
    Matrix halfQuarter = rotation_z(M_PI_4);
    Matrix fullQuarter = rotation_z(M_PI_2);
    Tuple point = Tuple::point(0, 1, 0);

    EXPECT_EQ(halfQuarter * point, Tuple::point(-M_SQRT2 / 2, M_SQRT2 / 2, 0));
    EXPECT_EQ(fullQuarter * point, Tuple::point(-1, 0, 0));
}

TEST(TransformTest, ShearingXY) {
    Matrix transform = shearing(1, 0, 0, 0, 0, 0);
    Tuple point = Tuple::point(2, 3, 4);

    EXPECT_EQ(transform * point, Tuple::point(5, 3, 4));
}

TEST(TransformTest, ShearingXZ) {
    Matrix transform = shearing(0, 1, 0, 0, 0, 0);
    Tuple point = Tuple::point(2, 3, 4);

    EXPECT_EQ(transform * point, Tuple::point(6, 3, 4));
}

TEST(TransformTest, ShearingYX) {
    Matrix transform = shearing(0, 0, 1, 0, 0, 0);
    Tuple point = Tuple::point(2, 3, 4);

    EXPECT_EQ(transform * point, Tuple::point(2, 5, 4));
}

TEST(TransformTest, ShearingYZ) {
    Matrix transform = shearing(0, 0, 0, 1, 0, 0);
    Tuple point = Tuple::point(2, 3, 4);

    EXPECT_EQ(transform * point, Tuple::point(2, 7, 4));
}

TEST(TransformTest, ShearingZX) {
    Matrix transform = shearing(0, 0, 0, 0, 1, 0);
    Tuple point = Tuple::point(2, 3, 4);

    EXPECT_EQ(transform * point, Tuple::point(2, 3, 6));
}

TEST(TransformTest, ShearingZY) {
    Matrix transform = shearing(0, 0, 0, 0, 0, 1);
    Tuple point = Tuple::point(2, 3, 4);

    EXPECT_EQ(transform * point, Tuple::point(2, 3, 7));
}

TEST(TransformTest, SequenceTransformations) {
    Tuple point = Tuple::point(1, 0, 1);
    Matrix a = rotation_x(M_PI_2);
    Matrix b = scaling(5, 5, 5);
    Matrix c = translation(10, 5, 7);

    Tuple p2 = a * point;
    ASSERT_EQ(p2, Tuple::point(1, -1, 0));
    Tuple p3 = b * p2;
    ASSERT_EQ(p3, Tuple::point(5, -5, 0));
    Tuple p4 = c * p3;
    ASSERT_EQ(p4, Tuple::point(15, 0, 7));
}

TEST(TransformTest, ChainingTransformations) {
    Tuple point = Tuple::point(1, 0, 1);
    Matrix a = rotation_x(M_PI_2);
    Matrix b = scaling(5, 5, 5);
    Matrix c = translation(10, 5, 7);

    EXPECT_EQ(c * b * a * point, Tuple::point(15, 0, 7));
}
