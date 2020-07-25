#include "camera.h"

Camera::Camera(int hsize, int vsize, float fov) : hsize(hsize), vsize(vsize), fov(fov),
                                                  _transform(Matrix::identity()), _inverse(Matrix::identity()) {
    float half_view = tanf(fov / 2);
    float aspect = (float) hsize / vsize;

    if (aspect > 1) {
        half_width = half_view;
        half_height = half_view / aspect;
    } else {
        half_width = half_view * aspect;
        half_height = half_view;
    }

    pixel_size = (half_width * 2) / hsize;
}

Matrix Camera::transform() {
    return _transform;
}

void Camera::transform(const Matrix &trans) {
    _transform = trans;
    _inverse = trans.inverse();
}

Matrix Camera::inverse() {
    return _inverse;
}

Ray Camera::ray_to_pixel(int x, int y) {
    // Offset from edge of camera to pixel center
    float xoffset = (x + 0.5) * pixel_size;
    float yoffset = (y + 0.5) * pixel_size;

    // Untransformed coordinates of pixel in world space
    // Camera looks towards -Z (canvas is at -1 Z)
    float world_x = half_width - xoffset;
    float world_y = half_height - yoffset;

    // Transform canvas point and origin
    Tuple pixel = _inverse * Tuple::point(world_x, world_y, -1);
    Tuple origin = _inverse * Tuple::point(0, 0, 0);

    // Compute direction vector for ray
    Tuple direction = (pixel - origin).normalized();

    return Ray(origin, direction);
}

Canvas Camera::render(const World& world) {
    Canvas canvas = Canvas(hsize, vsize);

    for (int x = 0; x < canvas.width; x++) {
        for (int y = 0; y < canvas.height; y++) {
            Ray ray = ray_to_pixel(x, y);
            Color color = world.color_at(ray, 5);
            canvas.write_pixel(x, y, color);
        }
    }

    return canvas;
}
