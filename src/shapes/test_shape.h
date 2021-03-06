#pragma once

#include "shape.h"

class TestShape : public Shape {

public:
    TestShape();
    TestShape(const Matrix& transform);

    Bounds bounds() const override;

private:
    virtual std::vector<Intersection> local_intersect(const Ray& local_ray) const;
    virtual Tuple local_normal_at(const Tuple& local_point, const Intersection& intersection) const;

};
