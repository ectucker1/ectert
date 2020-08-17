#include "shape.h"
#include "group.h"

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

Tuple Shape::world_to_object(const Tuple& world) const {
    if (parent != nullptr) {
        return _inverse * parent->world_to_object(world);
    }

    return _inverse * world;
}

Tuple Shape::normal_to_world(const Tuple& normal) const {
    Tuple world_normal = _inverse.transposed() * normal;
    world_normal.w = 0;
    world_normal = world_normal.normalized();

    if (parent != nullptr) {
        world_normal = parent->normal_to_world(world_normal);
    }

    return world_normal;
}

Tuple Shape::normal_at(const Tuple &point, const Intersection& intersection) const {
    Tuple local_point = world_to_object(point);
    Tuple local_normal = local_normal_at(local_point, intersection);
    return normal_to_world(local_normal);
}
