#include "gtest/gtest.h"
#include "math/tuple.h"
#include <cmath>

TEST(TupleTest, TupleWithWOneIsPoint) {
	Tuple tuple = Tuple(4.3f, -4.2f, 3.1f, 1.0f);

	EXPECT_FLOAT_EQ(tuple.x, 4.3f);
    EXPECT_FLOAT_EQ(tuple.y, -4.2f);
    EXPECT_FLOAT_EQ(tuple.z, 3.1f);
    EXPECT_FLOAT_EQ(tuple.w, 1.0f);
	EXPECT_TRUE(tuple.is_point());
	EXPECT_FALSE(tuple.is_vector());
}

TEST(TupleTest, TupleWithWZeroIsVector) {
	Tuple tuple = Tuple(4.3f, -4.2f, 3.1f, 0.0f);

    EXPECT_FLOAT_EQ(tuple.x, 4.3f);
    EXPECT_FLOAT_EQ(tuple.y, -4.2f);
    EXPECT_FLOAT_EQ(tuple.z, 3.1f);
    EXPECT_FLOAT_EQ(tuple.w, 0.0f);
	EXPECT_TRUE(tuple.is_vector());
	EXPECT_FALSE(tuple.is_point());
}

TEST(TupleTest, PointConstructorCreatesWOne) {
	Tuple tuple = Tuple::point(4.0f, -4.0f, 3.0f);

	EXPECT_EQ(tuple, Tuple(4.0f, -4.0f, 3.0f, 1.0f));
}

TEST(TupleTest, VectorConstructorCreatesWZero) {
	Tuple tuple = Tuple::vector(4.0f, -4.0f, 3.0f);

    EXPECT_EQ(tuple, Tuple(4.0f, -4.0f, 3.0f, 0.0f));
}

TEST(TupleTest, EqualityAccurate) {
    Tuple a = Tuple(4.3f, -4.2f, 3.1f, 1.0f);
    Tuple a2 = Tuple(4.3f, -4.2f, 3.1f, 1.0f);
    Tuple b = Tuple(4.3f, -4.2f, 3.1f, 0.0f);

    EXPECT_TRUE(a == a2);
    EXPECT_FALSE(a == b);
    EXPECT_FALSE(b == a);
}

TEST(TupleTest, TupleAdditon) {
    Tuple a = Tuple(3, -2, 5, 1);
    Tuple b = Tuple(-2, 3, 1, 0);

    EXPECT_EQ(a + b, Tuple(1, 1, 6, 1));
}

TEST(TupleTest, SubtractingPoints) {
    Tuple p1 = Tuple::point(3, 2, 1);
    Tuple p2 = Tuple::point(5, 6, 7);

    EXPECT_EQ(p1 - p2, Tuple::vector(-2, -4, -6));
}

TEST(TupleTest, SubtractingVectorPoint) {
    Tuple p = Tuple::point(3, 2, 1);
    Tuple v = Tuple::vector(5, 6, 7);

    EXPECT_EQ(p - v, Tuple::point(-2, -4, -6));
}

TEST(TupleTest, SubtractingVectors) {
    Tuple v1 = Tuple::vector(3, 2, 1);
    Tuple v2 = Tuple::vector(5, 6, 7);

    EXPECT_EQ(v1 - v2, Tuple::vector(-2, -4, -6));
}

TEST(TupleTest, NegatingTuples) {
    Tuple tuple = Tuple(1, -2, 3, -4);

    EXPECT_EQ(-tuple, Tuple(-1, 2, -3, 4));
}

TEST(TupleTest, MultiplyingScalar) {
    Tuple tuple = Tuple(1, -2, 3, -4);

    EXPECT_EQ(tuple * 3.5f, Tuple(3.5f, -7.0f, 10.5f, -14.0f));
}

TEST(TupleTest, MultiplyingFraction) {
    Tuple tuple = Tuple(1, -2, 3, -4);

    EXPECT_EQ(tuple * 0.5f, Tuple(0.5f, -1.0f, 1.5f, -2.0f));
}

TEST(TupleTest, DividingScalr) {
    Tuple tuple = Tuple(1, -2, 3, -4);

    EXPECT_EQ(tuple / 2.0f, Tuple(0.5f, -1.0f, 1.5f, -2.0f));
}

TEST(TupleTest, MagnitudeSquareVector) {
    Tuple v1 = Tuple::vector(1, 0, 0);
    Tuple v2 = Tuple::vector(0, 1, 0);
    Tuple v3 = Tuple::vector(0, 0, 1);
    Tuple v4 = Tuple::vector(1, 2, 3);
    Tuple v5 = Tuple::vector(-1, -2, -3);

    EXPECT_FLOAT_EQ(v1.magnitude_sq(), 1);
    EXPECT_FLOAT_EQ(v2.magnitude_sq(), 1);
    EXPECT_FLOAT_EQ(v3.magnitude_sq(), 1);
    EXPECT_FLOAT_EQ(v4.magnitude_sq(), 14);
    EXPECT_FLOAT_EQ(v5.magnitude_sq(), 14);
}

TEST(TupleTest, MagnitudeVector) {
    Tuple v1 = Tuple::vector(1, 0, 0);
    Tuple v2 = Tuple::vector(0, 1, 0);
    Tuple v3 = Tuple::vector(0, 0, 1);
    Tuple v4 = Tuple::vector(1, 2, 3);
    Tuple v5 = Tuple::vector(-1, -2, -3);

    EXPECT_FLOAT_EQ(v1.magnitude(), 1);
    EXPECT_FLOAT_EQ(v2.magnitude(), 1);
    EXPECT_FLOAT_EQ(v3.magnitude(), 1);
    EXPECT_FLOAT_EQ(v4.magnitude(), sqrt(14));
    EXPECT_FLOAT_EQ(v5.magnitude(), sqrt(14));
}

TEST(TupleTest, NormalizeVector) {
    Tuple v1 = Tuple::vector(4, 0, 0);
    Tuple v2 = Tuple::vector(1, 2, 3);

    EXPECT_EQ(v1.normalized(), Tuple::vector(1, 0, 0));
    EXPECT_EQ(v2.normalized(), Tuple::vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)));
}

TEST(TupleTest, NormalizedMagnitude) {
    Tuple v1 = Tuple::vector(4, 0, 0);
    Tuple v2 = Tuple::vector(1, 2, 3);

    EXPECT_FLOAT_EQ(v1.normalized().magnitude(), 1);
    EXPECT_FLOAT_EQ(v2.normalized().magnitude(), 1);
}

TEST(TupleTest, DotProduct) {
    Tuple v1 = Tuple::vector(1, 2, 3);
    Tuple v2 = Tuple::vector(2, 3, 4);

    EXPECT_FLOAT_EQ(v1.dot(v2), 20);
}

TEST(TupleTest, CrossProduct) {
    Tuple v1 = Tuple::vector(1, 2, 3);
    Tuple v2 = Tuple::vector(2, 3, 4);

    EXPECT_EQ(v1.cross(v2), Tuple::vector(-1, 2, -1));
    EXPECT_EQ(v2.cross(v1), Tuple::vector(1, -2, 1));
}
