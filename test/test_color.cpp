#include "gtest/gtest.h"
#include "math/color.h"

TEST(ColorTest, ConstructingColors) {
    Color c1 = Color(-0.5f, 0.4f, 1.7f);
    Color c2 = Color();

    EXPECT_FLOAT_EQ(c1.r, -0.5f);
    EXPECT_FLOAT_EQ(c1.g, 0.4f);
    EXPECT_FLOAT_EQ(c1.b, 1.7f);
    EXPECT_FLOAT_EQ(c2.r, 0);
    EXPECT_FLOAT_EQ(c2.g, 0);
    EXPECT_FLOAT_EQ(c2.b, 0);
}

TEST(ColorTest, AddingColors) {
    Color c1 = Color(0.9f, 0.6f, 0.75f);
    Color c2 = Color(0.7f, 0.1f, 0.25f);

    EXPECT_EQ(c1 + c2, Color(1.6f, 0.7f, 1.0f));
}

TEST(ColorTest, SubtractingColors) {
    Color c1 = Color(0.9f, 0.6f, 0.75f);
    Color c2 = Color(0.7f, 0.1f, 0.25f);

    EXPECT_EQ(c1 - c2, Color(0.2f, 0.5f, 0.5f));
}

TEST(ColorTest, MultiplyingColors) {
    Color c1 = Color(1.0f, 0.2f, 0.4f);
    Color c2 = Color(0.9f, 1.0f, 0.1f);

    EXPECT_EQ(c1 * c2, Color(0.9f, 0.2f, 0.04f));
}
