#pragma once

class Intersection;
class Group;
class Bounds;

#include "intersection/ray.h"
#include "intersection/intersection.h"
#include "light/material.h"
#include <vector>
#include <memory>

class Shape : public std::enable_shared_from_this<Shape> {

public:
    std::shared_ptr<Material> material;
    std::shared_ptr<Group> parent;

    Shape();
    Shape(const Matrix& transform);

    Matrix transform() const;
    void transform(const Matrix& trans);

    Matrix inverse() const;

    std::vector<Intersection> intersect(const Ray& ray) const;

    Tuple world_to_object(const Tuple& world) const;
    Tuple normal_to_world(const Tuple& normal) const;

    Tuple normal_at(const Tuple& point, const Intersection& intersection = Intersection::NIL) const;

    virtual Bounds bounds() const = 0;

private:
    Matrix _transform;
    Matrix _inverse;

    virtual std::vector<Intersection> local_intersect(const Ray& local_ray) const = 0;
    virtual Tuple local_normal_at(const Tuple& local_point, const Intersection& intersection) const = 0;

};
