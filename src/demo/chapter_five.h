#pragma once

#include "shapes/sphere.h"
#include "intersection/intersection.h"
#include "canvas.h"
#include "files/ppm.h"

void run_chapter_five() {
    Canvas canvas = Canvas(512, 512);
    Color shadow = Color(0, 1, 1);

    Sphere sphere = Sphere(rotation_z(1) * scaling(0.5, 1, 1));
    float wallZ = 10;
    float wallSize = 7;
    float pixelSize = wallSize / canvas.width;
    float half = wallSize / 2;

    Ray ray = Ray(Tuple::point(0, 0, -5), Tuple::vector(0, 0, 1));

    for (int x = 0; x < canvas.width; x++) {
        float worldX = -half + pixelSize * x;
        for (int y = 0; y < canvas.height; y++) {
            float worldY = half - pixelSize * y;
            Tuple pos = Tuple::point(worldX, worldY, wallZ);

            ray.direction = (pos - ray.origin).normalized();
            std::vector<Intersection> xs = (sphere.intersect(ray));
            sort_intersections(xs);

            if (!(Intersection::NIL == hit(xs))) {
                canvas.write_pixel(x, y, shadow);
            }
        }
    }

    write_ppm(canvas, "chapter5.ppm");
}