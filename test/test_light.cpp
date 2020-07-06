#include "gtest/gtest.h"
#include "light/point_light.h"

TEST(LightTest, CreatingPointLight) {
    PointLight light = PointLight(Tuple::point(0, 0, 0), Color(1, 1, 1));

    EXPECT_EQ(light.position, Tuple::point(0, 0, 0));
    EXPECT_EQ(light.intensity, Color(1, 1, 1));
}
