#include "gtest/gtest.h"
#include "shapes/test_shape.h"
#include "math/transform.h"
#include <cmath>

TEST(ShapeTest, DefaultTransform) {
    TestShape shape = TestShape();

    EXPECT_EQ(shape.transform(), Matrix::identity());
    EXPECT_EQ(shape.inverse(), Matrix::identity().inverse());
}

TEST(ShapeTest, ChangingTransform) {
    TestShape shape = TestShape();
    Matrix transform = translation(2, 3, 4);

    shape.transform(transform);
    EXPECT_EQ(shape.transform(), transform);
    EXPECT_EQ(shape.inverse(), transform.inverse());
}

TEST(ShapeTest, IntersectingScaled) {
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    TestShape shape = TestShape(scaling(2, 2, 2));

    std::vector<Intersection> results = shape.intersect(ray);
    // TODO figure out a way to test this without sacrificing const
}

TEST(ShapeTest, IntersectingTranslated) {
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    TestShape shape = TestShape(translation(5, 0, 0));

    std::vector<Intersection> results = shape.intersect(ray);
    // TODO figure out a way to test this without sacrificing const
}

TEST(ShapeTest, NormalTranslated) {
    TestShape shape = TestShape();
    shape.transform(translation(0, 1, 0));

    EXPECT_EQ(shape.normal_at(Tuple::point(0.0f, 1.70711f, -0.70711f)), Tuple::vector(0.0f, 0.70711f, -0.70711f));
}

TEST(ShapeTest, NormalTransformed) {
    TestShape shape = TestShape();
    shape.transform(scaling(1, 0.5f, 1) * rotation_z(M_PI / 5));

    EXPECT_EQ(shape.normal_at(Tuple::point(0.0f, M_SQRT2 / 2, -M_SQRT2 / 2)), Tuple::vector(0, 0.97014f, -0.24254f));
}

TEST(ShapeTest, DefaultMaterial) {
    TestShape shape = TestShape();

    EXPECT_EQ(shape.material, Material());
}

TEST(ShapeTest, AssignedMaterial) {
    TestShape shape = TestShape();
    Material mat = Material();
    mat.ambient = 1;
    shape.material = mat;

    EXPECT_EQ(shape.material, mat);
}
