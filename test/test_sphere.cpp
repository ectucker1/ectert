#include "gtest/gtest.h"
#include "intersection/sphere.h"
#include "math/transform.h"
#include <cmath>

TEST(SphereTest, IntersectingSphere) {
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere sphere = Sphere();

    std::vector<Intersection> results = sphere.intersect(ray);
    ASSERT_EQ(results.size(), 2);
    EXPECT_FLOAT_EQ(results[0].t, 4.0);
    EXPECT_FLOAT_EQ(results[1].t, 6.0);
}

TEST(SphereTest, IntersectingSphereTangent) {
    Ray ray = Ray(Tuple::point(0, 1, -5), Tuple::vector(0, 0, 1));
    Sphere sphere = Sphere();

    std::vector<Intersection> results = sphere.intersect(ray);
    ASSERT_EQ(results.size(), 2);
    EXPECT_FLOAT_EQ(results[0].t, 5.0);
    EXPECT_FLOAT_EQ(results[1].t, 5.0);
}

TEST(SphereTest, MissingSphere) {
    Ray ray = Ray(Tuple::point(0, 2, -5), Tuple::vector(0, 0, 1));
    Sphere sphere = Sphere();

    std::vector<Intersection> results = sphere.intersect(ray);
    ASSERT_EQ(results.size(), 0);
}

TEST(SphereTest, RayInsideSphere) {
    Ray ray = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));
    Sphere sphere = Sphere();

    std::vector<Intersection> results = sphere.intersect(ray);
    ASSERT_EQ(results.size(), 2);
    EXPECT_FLOAT_EQ(results[0].t, -1.0);
    EXPECT_FLOAT_EQ(results[1].t, 1.0);
}

TEST(SphereTest, RayAfterSphere) {
    Ray ray = Ray(Tuple::point(0, 0, 5), Tuple::vector(0, 0, 1));
    Sphere sphere = Sphere();

    std::vector<Intersection> results = sphere.intersect(ray);
    ASSERT_EQ(results.size(), 2);
    EXPECT_FLOAT_EQ(results[0].t, -6.0);
    EXPECT_FLOAT_EQ(results[1].t, -4.0);
}

TEST(SphereTest, DefaultTransform) {
    Sphere sphere = Sphere();

    EXPECT_EQ(sphere.transform, Matrix::identity());
}

TEST(SphereTest, ChangingTransform) {
    Sphere sphere = Sphere();
    Matrix transform = translation(2, 3, 4);

    sphere.transform = transform;
    EXPECT_EQ(sphere.transform, transform);
}

TEST(SphereTest, IntersectingScaled) {
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere sphere = Sphere(scaling(2, 2, 2));

    std::vector<Intersection> results = sphere.intersect(ray);
    ASSERT_EQ(results.size(), 2);
    EXPECT_FLOAT_EQ(results[0].t, 3);
    EXPECT_FLOAT_EQ(results[1].t, 7);
}

TEST(SphereTest, IntersectingTranslated) {
    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));
    Sphere sphere = Sphere(translation(5, 0, 0));

    std::vector<Intersection> results = sphere.intersect(ray);
    ASSERT_EQ(results.size(), 0);
}

TEST(SphereTest, NormalsAxes) {
    Sphere sphere = Sphere();

    EXPECT_EQ(sphere.normal_at(Tuple::point(1, 0, 0)), Tuple::vector(1, 0, 0));
    EXPECT_EQ(sphere.normal_at(Tuple::point(0, 1, 0)), Tuple::vector(0, 1, 0));
    EXPECT_EQ(sphere.normal_at(Tuple::point(0, 0, 1)), Tuple::vector(0, 0, 1));
}

TEST(SphereTest, NormalOffAxis) {
    Sphere sphere = Sphere();

    EXPECT_EQ(sphere.normal_at(Tuple::point(std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3)),
            Tuple::vector(std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3));
}

TEST(SphereTest, NormalIsNormalized) {
    Sphere sphere = Sphere();
    Tuple normal = sphere.normal_at(Tuple::point(std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3, std::sqrt(3.0f) / 3));

    EXPECT_EQ(normal, normal.normalized());
}

TEST(SphereTest, NormalTranslated) {
    Sphere sphere = Sphere();
    sphere.transform = translation(0, 1, 0);

    EXPECT_EQ(sphere.normal_at(Tuple::point(0.0f, 1.70711f, -0.70711f)), Tuple::vector(0.0f, 0.70711f, -0.70711f));
}

TEST(SphereTest, NormalTransformed) {
    Sphere sphere = Sphere();
    sphere.transform = scaling(1, 0.5f, 1) * rotation_z(M_PI / 5);

    EXPECT_EQ(sphere.normal_at(Tuple::point(0.0f, M_SQRT2 / 2, -M_SQRT2 / 2)), Tuple::vector(0, 0.97014f, -0.24254f));
}

TEST(SphereTest, DefaultMaterial) {
    Sphere sphere = Sphere();

    EXPECT_EQ(sphere.material, Material());
}

TEST(SphereTest, AssignedMaterial) {
    Sphere sphere = Sphere();
    Material mat = Material();
    mat.ambient = 1;
    sphere.material = mat;

    EXPECT_EQ(sphere.material, mat);
}
