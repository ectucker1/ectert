#include "gtest/gtest.h"
#include "canvas.h"
#include "math/color.h"

TEST(CanvasTest, ConstructingCanvas) {
    Canvas canvas = Canvas(10, 20);

    EXPECT_EQ(canvas.width, 10);
    EXPECT_EQ(canvas.height, 20);

    for (int x = 0; x < canvas.width; x++) {
        for (int y = 0; y < canvas.height; y++) {
            EXPECT_EQ(canvas.get_pixel(x, y), Color(0, 0, 0));
        }
    }
}

TEST(CanvasTest, WritingCanvas) {
    Canvas canvas = Canvas(10, 20);
    Color red = Color(1, 0, 0);

    canvas.write_pixel(2, 3, red);

    EXPECT_EQ(canvas.get_pixel(2, 3), red);
}
