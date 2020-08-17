#include "gtest/gtest.h"
#include "shapes/triangle.h"
#include "math/bounds.h"
#include "intersection/hit.h"

TEST(TriangleTest, ConstructingTriangle) {
    Tuple p1 = Tuple::point(0, 1, 0);
    Tuple p2 = Tuple::point(-1, 0, 0);
    Tuple p3 = Tuple::point(1, 0, 0);

    Triangle tri = Triangle(p1, p2, p3);

    EXPECT_EQ(tri.p1(), p1);
    EXPECT_EQ(tri.p2(), p2);
    EXPECT_EQ(tri.p3(), p3);
    EXPECT_EQ(tri.e1(), Tuple::vector(-1, -1, 0));
    EXPECT_EQ(tri.e2(), Tuple::vector(1, -1, 0));
    EXPECT_EQ(tri.n1(), Tuple::vector(0, 0, -1));
    EXPECT_EQ(tri.n2(), Tuple::vector(0, 0, -1));
    EXPECT_EQ(tri.n3(), Tuple::vector(0, 0, -1));
}

TEST(TriangleTest, NormalOnFlatTriangle) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));

    EXPECT_EQ(tri->normal_at(Tuple::point(0, 0.5, 0)), tri->n1());
    EXPECT_EQ(tri->normal_at(Tuple::point(-0.5, 0.75, 0)), tri->n1());
    EXPECT_EQ(tri->normal_at(Tuple::point(0.5, 0.25, 0)), tri->n1());
}

TEST(TriangleTest, IntersectingRayParallelTriangle) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));
    auto ray = Ray(Tuple::point(0, -1, -2), Tuple::vector(0, 1, 0));

    auto xs = tri->intersect(ray);
    EXPECT_TRUE(xs.empty());
}

TEST(TriangeTest, RayMissesP1P3Edge) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));
    auto ray = Ray(Tuple::point(1, 1, -2), Tuple::vector(0, 0, 1));

    auto xs = tri->intersect(ray);
    EXPECT_TRUE(xs.empty());
}

TEST(TriangeTest, RayMissesP1P2Edge) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));
    auto ray = Ray(Tuple::point(-1, 1, -2), Tuple::vector(0, 0, 1));

    auto xs = tri->intersect(ray);
    EXPECT_TRUE(xs.empty());
}

TEST(TriangeTest, RayMissesP2P3Edge) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));
    auto ray = Ray(Tuple::point(0, -1, -2), Tuple::vector(0, 0, 1));

    auto xs = tri->intersect(ray);
    EXPECT_TRUE(xs.empty());
}

TEST(TriangeTest, RayHitsTriangle) {
    auto tri = std::make_shared<Triangle>(Tuple::point(0, 1, 0), Tuple::point(-1, 0, 0), Tuple::point(1, 0, 0));
    auto ray = Ray(Tuple::point(0, 0.5, -2), Tuple::vector(0, 0, 1));

    auto xs = tri->intersect(ray);
    ASSERT_EQ(xs.size(), 1);
    EXPECT_EQ(xs[0].t, 2);
}

TEST(TriangleTest, ConstructingSmoothTriangle) {
    Tuple p1 = Tuple::point(0, 1, 0);
    Tuple p2 = Tuple::point(-1, 0, 0);
    Tuple p3 = Tuple::point(1, 0, 0);
    Tuple n1 = Tuple::vector(0, 1, 0);
    Tuple n2 = Tuple::vector(-1, 0, 0);
    Tuple n3 = Tuple::vector(1, 0, 0);

    Triangle tri = Triangle(p1, p2, p3, n1, n2, n3);

    EXPECT_EQ(tri.p1(), p1);
    EXPECT_EQ(tri.p2(), p2);
    EXPECT_EQ(tri.p3(), p3);
    EXPECT_EQ(tri.e1(), Tuple::vector(-1, -1, 0));
    EXPECT_EQ(tri.e2(), Tuple::vector(1, -1, 0));
    EXPECT_EQ(tri.n1(), n1);
    EXPECT_EQ(tri.n2(), n2);
    EXPECT_EQ(tri.n3(), n3);
}

TEST(TriangleTest, IntersectionStoresUV) {
    Tuple p1 = Tuple::point(0, 1, 0);
    Tuple p2 = Tuple::point(-1, 0, 0);
    Tuple p3 = Tuple::point(1, 0, 0);
    Tuple n1 = Tuple::vector(0, 1, 0);
    Tuple n2 = Tuple::vector(-1, 0, 0);
    Tuple n3 = Tuple::vector(1, 0, 0);

    auto tri = std::make_shared<Triangle>(p1, p2, p3, n1, n2, n3);
    Ray ray = Ray(Tuple::point(-0.2, 0.3, -2), Tuple::vector(0, 0, 1));

    auto xs = tri->intersect(ray);

    ASSERT_EQ(xs.size(), 1);
    EXPECT_FLOAT_EQ(xs[0].u, 0.45);
    EXPECT_FLOAT_EQ(xs[0].v, 0.25);
}

TEST(TriangleTest, SmoothTriangleInterpolatesNormal) {
    Tuple p1 = Tuple::point(0, 1, 0);
    Tuple p2 = Tuple::point(-1, 0, 0);
    Tuple p3 = Tuple::point(1, 0, 0);
    Tuple n1 = Tuple::vector(0, 1, 0);
    Tuple n2 = Tuple::vector(-1, 0, 0);
    Tuple n3 = Tuple::vector(1, 0, 0);

    auto tri = std::make_shared<Triangle>(p1, p2, p3, n1, n2, n3);
    Intersection x = Intersection(1, tri, 0.45, 0.25);

    EXPECT_EQ(tri->normal_at(Tuple::point(0, 0, 0), x), Tuple::vector(-0.5547, 0.83205, 0));
}

TEST(TriangleTest, PreparingHitSmoothTriangle) {
    Tuple p1 = Tuple::point(0, 1, 0);
    Tuple p2 = Tuple::point(-1, 0, 0);
    Tuple p3 = Tuple::point(1, 0, 0);
    Tuple n1 = Tuple::vector(0, 1, 0);
    Tuple n2 = Tuple::vector(-1, 0, 0);
    Tuple n3 = Tuple::vector(1, 0, 0);

    auto tri = std::make_shared<Triangle>(p1, p2, p3, n1, n2, n3);
    Ray ray = Ray(Tuple::point(-0.2, 0.3, -2), Tuple::vector(0, 0, 1));
    Intersection x = Intersection(1, tri, 0.45, 0.25);
    std::vector<Intersection> xs = {x};

    Hit hit = Hit(x, ray, xs);

    EXPECT_EQ(hit.normalv, Tuple::vector(-0.5547, 0.83205, 0));
}
