#pragma once

#include "shapes/sphere.h"
#include "intersection/intersection.h"
#include "math/transform.h"
#include "canvas.h"
#include "files/ppm.h"

void run_chapter_six() {
    Canvas canvas = Canvas(512, 512);

    Sphere sphere = Sphere();
    sphere.material.color = Color(0x90 / 255.0f, 0xbe / 255.0f, 0x6d / 255.0f);
    sphere.material.ambient = 0.15;
    sphere.material.diffuse = 0.8;
    sphere.material.specular = 0.1;
    sphere.material.shininess = 400.0;

    PointLight light = PointLight(Tuple::point(-15, 8, -10), Color(1, 1, 1.5));

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
            Intersection hitPoint = hit(xs);

            if (!(Intersection::NIL == hitPoint)) {
                Tuple point = ray.position(hitPoint.t);
                Tuple normal = sphere.normal_at(point);
                Tuple eye = -ray.direction;

                Color color = sphere.material.lighting(light, point, eye, normal, false);

                canvas.write_pixel(x, y, color);
            }
        }
    }

    write_ppm(canvas, "chapter6.ppm");
}