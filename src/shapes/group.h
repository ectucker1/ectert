#pragma once

#include "shape.h"
#include "math/bounds.h"

class Group : public Shape {

    using container = std::vector<std::shared_ptr<Shape>>;
    using iterator = typename container::iterator;
    using const_iterator = typename container::const_iterator;

public:
    Group();
    Group(const Matrix& transform);
    int size() const;

    void add_child(std::shared_ptr<Shape> shape);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    Bounds bounds() const override;

private:
    std::vector<std::shared_ptr<Shape>> _shapes;
    Bounds _bounds;

    void expand_bounds(const std::shared_ptr<Shape> shape);

    std::vector<Intersection> local_intersect(const Ray& local_ray) const override;
    Tuple local_normal_at(const Tuple& local_point, const Intersection& intersection) const override;


};
