#include "gtest/gtest.h"
#include "pattern/test_pattern.h"
#include "pattern/striped_pattern.h"
#include "pattern/gradient_pattern.h"
#include "pattern/ring_pattern.h"
#include "pattern/checker_pattern.h"
#include "shapes/sphere.h"
#include "math/transform.h"

TEST(PatternTest, DefaultPatternTransform) {
    TestPattern pattern = TestPattern();

    EXPECT_EQ(pattern.transform(), Matrix::identity());
    EXPECT_EQ(pattern.inverse(), Matrix::identity());
}

TEST(PatternTest, AssigningPatternTransform) {
    TestPattern pattern = TestPattern();
    pattern.transform(translation(1, 2, 3));

    EXPECT_EQ(pattern.transform(), translation(1, 2, 3));
    EXPECT_EQ(pattern.inverse(), translation(1, 2, 3).inverse());
}

TEST(PatternTest, PatternObjectTransform) {
    std::shared_ptr<Sphere> shape = std::make_shared<Sphere>(scaling(2, 2, 2));
    TestPattern pattern = TestPattern();

    EXPECT_EQ(pattern.sample_shape(shape, Tuple::point(2, 3, 4)), Color(1, 1.5, 2));
}

TEST(PatternTest, PatternPatternTransform) {
    std::shared_ptr<Sphere> shape = std::make_shared<Sphere>();
    TestPattern pattern = TestPattern();
    pattern.transform(scaling(2, 2, 2));

    EXPECT_EQ(pattern.sample_shape(shape, Tuple::point(2, 3, 4)), Color(1, 1.5, 2));
}

TEST(PatternTest, PatternBothTransform) {
    std::shared_ptr<Sphere> shape = std::make_shared<Sphere>(scaling(2, 2, 2));
    TestPattern pattern = TestPattern();
    pattern.transform(translation(0.5, 1, 1.5));

    EXPECT_EQ(pattern.sample_shape(shape, Tuple::point(2.5, 3, 3.5)), Color(0.75, 0.5, 0.25));
}

TEST(PatternTest, CreatingStripedPattern) {
    StripedPattern pattern = StripedPattern(Color::white, Color::black);

    EXPECT_EQ(pattern.a, Color::white);
    EXPECT_EQ(pattern.b, Color::black);
}

TEST(PatternTest, StripedPatternConstY) {
    StripedPattern pattern = StripedPattern(Color::white, Color::black);

    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 1, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 2, 0)), Color::white);
}

TEST(PatternTest, StripedPatternConstZ) {
    StripedPattern pattern = StripedPattern(Color::white, Color::black);

    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0, 1)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0, 2)), Color::white);
}

TEST(PatternTest, StripedPatternAlternatesX) {
    StripedPattern pattern = StripedPattern(Color::white, Color::black);

    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0.9, 0, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(1, 0, 0)), Color::black);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(-0.1, 0, 0)), Color::black);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(-1, 0, 0)), Color::black);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(-1.1, 0, 0)), Color::white);
}

TEST(PatternTest, GradientSmooth) {
    GradientPattern pattern = GradientPattern(Color::white, Color::black);

    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0.25, 0, 0)), Color(0.75, 0.75, 0.75));
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0.5, 0, 0)), Color(0.5, 0.5, 0.5));
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0.75, 0, 0)), Color(0.25, 0.25, 0.25));
}

TEST(PatternTest, RingExtendsXZ) {
    RingPattern pattern = RingPattern(Color::white, Color::black);

    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(1, 0, 0)), Color::black);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0, 1)), Color::black);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0.708, 0, 0.708)), Color::black);
}

TEST(PatternTest, CheckerRepeatX) {
    CheckerPattern pattern = CheckerPattern(Color::white, Color::black);

    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0.99, 0, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(1.01, 0, 0)), Color::black);
}

TEST(PatternTest, CheckerRepeatY) {
    CheckerPattern pattern = CheckerPattern(Color::white, Color::black);

    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0.99, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 1.01, 0)), Color::black);
}

TEST(PatternTest, CheckerRepeatZ) {
    CheckerPattern pattern = CheckerPattern(Color::white, Color::black);

    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 0.99, 0)), Color::white);
    EXPECT_EQ(pattern.sample_pattern(Tuple::point(0, 1.01, 0)), Color::black);
}
