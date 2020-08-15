#include "group.h"

Group::Group() {}

Group::Group(const Matrix &transform) : Shape(transform) {}

int Group::size() const {
    return shapes.size();
}

void Group::add_child(std::shared_ptr<Shape> shape) {
    shapes.push_back(shape);
    shape->parent = std::static_pointer_cast<Group>(shared_from_this());
}

Group::iterator Group::begin() {
    return shapes.begin();
}

Group::iterator Group::end() {
    return shapes.end();
}

Group::const_iterator Group::begin() const {
    return shapes.begin();
}

Group::const_iterator Group::end() const {
    return shapes.end();
}

std::vector<Intersection> Group::local_intersect(const Ray &local_ray) const {
    auto xs = std::vector<Intersection>();
    for (auto shape : shapes) {
        auto shapeXS = shape->intersect(local_ray);
        xs.insert(xs.end(), shapeXS.begin(), shapeXS.end());
    }
    return xs;
}

Tuple Group::local_normal_at(const Tuple &local_point) const {
    // Group does not have normals; local_intersect returns pointers to children
    return Tuple(0, 0, 0, 0);
}
