#include "gtest/gtest.h"
#include "shapes/test_shape.h"
#include "math/transform.h"
#include "shapes/sphere.h"
#include "shapes/group.h"
#include "light/lambertian_material.h"
#include "light/dielectric_material.h"
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
    auto shape = std::make_shared<TestShape>(scaling(2, 2, 2));

    std::vector<Intersection> results = shape->intersect(ray);
    // TODO figure out a way to test this without sacrificing const
}

TEST(ShapeTest, IntersectingTranslated) {
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    auto shape = std::make_shared<TestShape>(translation(5, 0, 0));

    std::vector<Intersection> results = shape->intersect(ray);
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

TEST(ShapeTest, AssignedMaterial) {
    TestShape shape = TestShape();
    auto mat = std::make_shared<DielectricMaterial>(2.0);
    shape.material = mat;

    EXPECT_EQ(shape.material, mat);
}

TEST(ShapeTest, DefaultParent) {
    TestShape shape = TestShape();

    EXPECT_EQ(shape.parent, nullptr);
}

TEST(ShapeTest, ConvertingWorldToObject) {
    auto g1 = std::make_shared<Group>(rotation_y(M_PI_2));
    auto g2 = std::make_shared<Group>(scaling(2, 2, 2));
    g1->add_child(g2);
    auto s = std::make_shared<Sphere>(translation(5, 0, 0));
    g2->add_child(s);

    EXPECT_EQ(s->world_to_object(Tuple::point(-2, 0, -10)), Tuple::point(0, 0, -1));
}

TEST(ShapeTest, ConvertingNormalToWorld) {
    auto g1 = std::make_shared<Group>(rotation_y(M_PI_2));
    auto g2 = std::make_shared<Group>(scaling(1, 2, 3));
    g1->add_child(g2);
    auto s = std::make_shared<Sphere>(translation(5, 0, 0));
    g2->add_child(s);

    EXPECT_EQ(s->normal_to_world(Tuple::vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3)), Tuple::vector(0.2857, 0.4286, -0.8571));
}

TEST(ShapeTest, FindingNormalOnChild) {
    auto g1 = std::make_shared<Group>(rotation_y(M_PI_2));
    auto g2 = std::make_shared<Group>(scaling(1, 2, 3));
    g1->add_child(g2);
    auto s = std::make_shared<Sphere>(translation(5, 0, 0));
    g2->add_child(s);

    EXPECT_EQ(s->normal_at(Tuple::point(1.7321, 1.1547, -5.5774)), Tuple::vector(0.2857, 0.4286, -0.8571));
}
