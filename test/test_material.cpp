#include "gtest/gtest.h"
#include "light/material.h"
#include <cmath>

TEST(MaterialTest, DefaultMaterial) {
    Material mat = Material();

    EXPECT_EQ(mat.color, Color(1, 1, 1));
    EXPECT_FLOAT_EQ(mat.ambient, 0.1);
    EXPECT_FLOAT_EQ(mat.diffuse, 0.9);
    EXPECT_FLOAT_EQ(mat.specular, 0.9);
    EXPECT_FLOAT_EQ(mat.shininess, 200.0);
}

TEST(MaterialTest, LightingEyeLightDirect) {
    Material mat = Material();
    Tuple position = Tuple::point(0, 0, 0);
    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light = PointLight(Tuple::point(0, 0, -10), Color(1, 1, 1));

    EXPECT_EQ(mat.lighting(light, position, eyev, normalv, false), Color(1.9f, 1.9f, 1.9f));
}

TEST(MaterialTest, LightingEye45) {
    Material mat = Material();
    Tuple position = Tuple::point(0, 0, 0);
    Tuple eyev = Tuple::vector(0, M_SQRT2 / 2, -M_SQRT2 / 2);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light = PointLight(Tuple::point(0, 0, -10), Color(1, 1, 1));

    EXPECT_EQ(mat.lighting(light, position, eyev, normalv, false), Color(1.0f, 1.0f, 1.0f));
}

TEST(MaterialTest, LightingLight45) {
    Material mat = Material();
    Tuple position = Tuple::point(0, 0, 0);
    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light = PointLight(Tuple::point(0, 10, -10), Color(1, 1, 1));

    EXPECT_EQ(mat.lighting(light, position, eyev, normalv, false), Color(0.7364f, 0.7364f, 0.7364f));
}

TEST(MaterialTest, LightingEyeLightOpposite45) {
    Material mat = Material();
    Tuple position = Tuple::point(0, 0, 0);
    Tuple eyev = Tuple::vector(0, -M_SQRT2 / 2, -M_SQRT2 / 2);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light = PointLight(Tuple::point(0, 10, -10), Color(1, 1, 1));

    EXPECT_EQ(mat.lighting(light, position, eyev, normalv, false), Color(1.6364f, 1.6364f, 1.6364f));
}

TEST(MaterialTest, LightingLightBehind) {
    Material mat = Material();
    Tuple position = Tuple::point(0, 0, 0);
    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light = PointLight(Tuple::point(0, 0, 10), Color(1, 1, 1));

    EXPECT_EQ(mat.lighting(light, position, eyev, normalv, false), Color(0.1f, 0.1f, 0.1f));
}

TEST(MaterialTest, LightingInShadow) {
    Material mat = Material();
    Tuple position = Tuple::point(0, 0, 0);
    Tuple eyev = Tuple::vector(0, 0, -1);
    Tuple normalv = Tuple::vector(0, 0, -1);
    PointLight light = PointLight(Tuple::point(0, 0, -10), Color(1, 1, 1));
    bool in_shadow = true;

    EXPECT_EQ(mat.lighting(light, position, eyev, normalv, in_shadow), Color(0.1f, 0.1f, 0.1f));
}
