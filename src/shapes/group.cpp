#include "group.h"
#include <cmath>

Group::Group() : _bounds(0, 0, 0, 0, 0, 0) {}

Group::Group(const Matrix &transform) : Shape(transform), _bounds(0, 0, 0, 0, 0, 0) {}

int Group::size() const {
    return _shapes.size();
}

void Group::add_child(std::shared_ptr<Shape> shape) {
    _shapes.push_back(shape);
    expand_bounds(shape);
    shape->parent = std::static_pointer_cast<Group>(shared_from_this());
}

Group::iterator Group::begin() {
    return _shapes.begin();
}

Group::iterator Group::end() {
    return _shapes.end();
}

Group::const_iterator Group::begin() const {
    return _shapes.begin();
}

Group::const_iterator Group::end() const {
    return _shapes.end();
}

std::vector<Intersection> Group::local_intersect(const Ray &local_ray) const {
    if (!_bounds.intersects(local_ray)) {
        return std::vector<Intersection>();
    }

    auto xs = std::vector<Intersection>();
    for (auto shape : _shapes) {
        auto shapeXS = shape->intersect(local_ray);
        xs.insert(xs.end(), shapeXS.begin(), shapeXS.end());
    }
    return xs;
}

Tuple Group::local_normal_at(const Tuple &local_point) const {
    // Group does not have normals; local_intersect returns pointers to children
    return Tuple(0, 0, 0, 0);
}

void Group::expand_bounds(const std::shared_ptr<Shape> shape) {
    auto shape_bounds = shape->bounds();

    // Might be a more efficient solution to infinity, but it currently breaks matrix-tuple multiplication
    if (shape_bounds.infinite()) {
        _bounds = Bounds(-INFINITY, INFINITY, -INFINITY, INFINITY, -INFINITY, INFINITY);
        return;
    }

    auto corners = std::vector<Tuple>();

    // Push all corners of the bounding box
    corners.push_back(Tuple::point(shape_bounds.minX, shape_bounds.minY, shape_bounds.minZ));
    corners.push_back(Tuple::point(shape_bounds.minX, shape_bounds.minY, shape_bounds.maxZ));
    corners.push_back(Tuple::point(shape_bounds.minX, shape_bounds.maxY, shape_bounds.minZ));
    corners.push_back(Tuple::point(shape_bounds.minX, shape_bounds.maxY, shape_bounds.maxZ));
    corners.push_back(Tuple::point(shape_bounds.maxX, shape_bounds.minY, shape_bounds.minZ));
    corners.push_back(Tuple::point(shape_bounds.maxX, shape_bounds.minY, shape_bounds.maxZ));
    corners.push_back(Tuple::point(shape_bounds.maxX, shape_bounds.maxY, shape_bounds.minZ));
    corners.push_back(Tuple::point(shape_bounds.maxX, shape_bounds.maxY, shape_bounds.maxZ));

    // Convert corners to group space
    for (int i = 0; i < corners.size(); i++) {
        corners[i] = shape->transform() * corners[i];
    }

    // Actually expand out the bounds
    for (Tuple corner : corners) {
        if (corner.x < _bounds.minX)
            _bounds.minX = corner.x;
        if (corner.x > _bounds.maxX)
            _bounds.maxX = corner.x;

        if (corner.y < _bounds.minY)
            _bounds.minY = corner.y;
        if (corner.y > _bounds.maxY)
            _bounds.maxY = corner.y;

        if (corner.z < _bounds.minZ)
            _bounds.minZ = corner.z;
        if (corner.z > _bounds.maxZ)
            _bounds.maxZ = corner.z;
    }
}

Bounds Group::bounds() const {
    return _bounds;
}
