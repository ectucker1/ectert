#pragma once

#include "shape.h"

class Triangle : public Shape {

public:
    Triangle(Tuple p1, Tuple p2, Tuple p3);

    Tuple p1() const;
    Tuple p2() const;
    Tuple p3() const;

    Tuple e1() const;
    Tuple e2() const;

    Tuple normal() const;

    Bounds bounds() const override;

private:
    Tuple _p1, _p2, _p3;
    Tuple _e1, _e2;
    Tuple _normal;

    std::vector<Intersection> local_intersect(const Ray& local_ray) const override;
    Tuple local_normal_at(const Tuple& local_point) const override;

};


