#include "gtest/gtest.h"
#include "world/camera.h"
#include "math/matrix.h"
#include "math/transform.h"
#include "world/world.h"
#include "light/gradient_background.h"
#include <cmath>

TEST(CameraTest, ConstructingCamera) {
    Camera c = Camera(160, 120, M_PI_2);

    EXPECT_EQ(c.hsize, 160);
    EXPECT_EQ(c.vsize, 120);
    EXPECT_FLOAT_EQ(c.fov, M_PI_2);
    EXPECT_EQ(c.transform(), Matrix::identity());
}

TEST(CameraTest, PixelSizeHorizantal) {
    Camera c = Camera(200, 125, M_PI_2);

    EXPECT_FLOAT_EQ(c.pixel_size, 0.01);
}

TEST(CameraTest, PixelSizeVertical) {
    Camera c = Camera(125, 200, M_PI_2);

    EXPECT_FLOAT_EQ(c.pixel_size, 0.01);
}

TEST(CameraTest, RayToCenter) {
    Camera c = Camera(201, 101, M_PI_2);

    Ray ray = c.ray_to_pixel(100, 50);
    EXPECT_EQ(ray.origin, Tuple::point(0, 0, 0));
    EXPECT_EQ(ray.direction, Tuple::vector(0, 0, -1));
}

TEST(CameraTest, RayToCorner) {
    Camera c = Camera(201, 101, M_PI_2);

    Ray ray = c.ray_to_pixel(0, 0);
    EXPECT_EQ(ray.origin, Tuple::point(0, 0, 0));
    EXPECT_EQ(ray.direction, Tuple::vector(0.66519, 0.33259, -0.66851));
}

TEST(CameraTest, RayCameraTransformed) {
    Camera c = Camera(201, 101, M_PI_2);
    c.transform(rotation_y(M_PI_4) * translation(0, -2, 5));

    Ray ray = c.ray_to_pixel(100, 50);
    EXPECT_EQ(ray.origin, Tuple::point(0, 2, -5));
    EXPECT_EQ(ray.direction, Tuple::vector(M_SQRT2 / 2, 0, -M_SQRT2 / 2));
}

TEST(CameraTest, RenderingWorld) {
    World world = World::example_world();
    Camera c = Camera(11, 11, M_PI_2);
    c.transform(view_transform(Tuple::point(0, 0, -5), Tuple::point(0, 0, 0), Tuple::point(0, 1, 0)));

    Canvas canvas = c.render(world);
    EXPECT_EQ(canvas.get_pixel(5, 5), Color(0.8, 1, 0.6));
}
