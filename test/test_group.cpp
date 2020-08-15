#include "gtest/gtest.h"
#include "shapes/group.h"
#include "shapes/test_shape.h"
#include "shapes/sphere.h"
#include "shapes/plane.h"
#include "math/transform.h"
#include <cmath>

TEST(GroupTest, CreatingNewGroup) {
    auto g = Group();

    EXPECT_EQ(g.transform(), Matrix::identity());
    EXPECT_EQ(g.size(), 0);
}

TEST(GroupTest, AddingChildToGroup) {
    auto g = std::make_shared<Group>();
    auto s = std::make_shared<TestShape>();

    g->add_child(s);
    EXPECT_EQ(g->size(), 1);
    // G contains s
    EXPECT_TRUE(std::find(g->begin(), g->end(), s) != g->end());
    EXPECT_EQ(s->parent, g);
}

TEST(GroupTest, IntersectingEmptyGroup) {
    auto g = std::make_shared<Group>();
    auto r = Ray(Tuple::point(0, 0, 0), Tuple::vector(0, 0, 1));

    auto xs = g->intersect(r);
    EXPECT_TRUE(xs.empty());
}

TEST(GroupTest, IntersectingNonemptyGroup) {
    auto g = std::make_shared<Group>();
    auto s1 = std::make_shared<Sphere>();
    auto s2 = std::make_shared<Sphere>(translation(0, 0, -3));
    auto s3 = std::make_shared<Sphere>(translation(5, 0, 0));
    g->add_child(s1);
    g->add_child(s2);
    g->add_child(s3);
    Ray r = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

    auto xs = g->intersect(r);
    xs = sort_intersections(xs);
    ASSERT_EQ(xs.size(), 4);
    EXPECT_EQ(xs[0].object, s2);
    EXPECT_EQ(xs[1].object, s2);
    EXPECT_EQ(xs[2].object, s1);
    EXPECT_EQ(xs[3].object, s1);
}

TEST(GroupTest, IntersectingTransformedGroup) {
    auto g = std::make_shared<Group>(scaling(2, 2, 2));
    auto s = std::make_shared<Sphere>(translation(5, 0, 0));
    g->add_child(s);
    Ray r = Ray(Tuple::point(10, 0, -10), Tuple::vector(0, 0, 1));

    auto xs = g->intersect(r);
    EXPECT_EQ(xs.size(), 2);
}

TEST(GroupTest, AddingChildrenExpandsBounds) {
    auto g = std::make_shared<Group>();

    auto s1 = std::make_shared<Sphere>();
    auto s2 = std::make_shared<Sphere>(translation(-1, 0, 0));
    auto s3 = std::make_shared<Sphere>(scaling(2, 3, 0.5));
    auto s4 = std::make_shared<Plane>();

    EXPECT_EQ(g->bounds(), Bounds(0, 0, 0, 0, 0, 0));
    g->add_child(s1);
    EXPECT_EQ(g->bounds(), Bounds(-1, 1, -1, 1, -1, 1));
    g->add_child(s2);
    EXPECT_EQ(g->bounds(), Bounds(-2, 1, -1, 1, -1, 1));
    g->add_child(s3);
    EXPECT_EQ(g->bounds(), Bounds(-2, 2, -3, 3, -1, 1));
    g->add_child(s4);
    EXPECT_EQ(g->bounds(), Bounds(-INFINITY, INFINITY, -INFINITY, INFINITY, -INFINITY, INFINITY));
}
