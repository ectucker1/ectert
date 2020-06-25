#include "chapter_two.h"

void run_chapter_two() {
    Projectile proj = Projectile(Tuple::point(0, 1, 0), Tuple::vector(1, 1, 0).normalized() * 8);
    Environment env = Environment(Tuple::vector(0, -0.1f, 0), Tuple::vector(-0.01f, 0, 0));

    Canvas canvas = Canvas(600, 200);
    Color plot = Color(0x81 / 255.0f, 0xb2 / 255.0f, 0x9a /255.0f);

    int ticks = 0;
    while (proj.position.y > 0) {
        int x = proj.position.x;
        int y = canvas.height - proj.position.y;
        canvas.write_pixel(x, y, plot);
        proj.tick(env);
        ticks++;
    }

    write_ppm(canvas, "chapter2.ppm");
}
