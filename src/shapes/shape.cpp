#include "shape.h"

Shape::Shape() : _transform(Matrix::identity()), _inverse(_transform.inverse()) {}
Shape::Shape(const Matrix& transform) : _transform(transform), _inverse(_transform.inverse()) {}

Matrix Shape::transform() const {
    return _transform;
}

void Shape::transform(const Matrix &trans) {
    _transform = trans;
    _inverse = trans.inverse();
}

Matrix Shape::inverse() const {
    return _inverse;
}

std::vector<Intersection> Shape::intersect(const Ray &ray) const {
    Ray local_ray = ray.transform(_inverse);

    return local_intersect(local_ray);
}

Tuple Shape::normal_at(const Tuple &point) const {
    Tuple local_point = _inverse * point;
    Tuple local_normal = local_normal_at(local_point);
    Tuple world_normal = _inverse.transposed() * local_normal;
    world_normal.w = 0;
    return world_normal.normalized();
}
