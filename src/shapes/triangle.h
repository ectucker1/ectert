#pragma once

#include "shape.h"

class Triangle : public Shape {

public:
    Triangle(Tuple p1, Tuple p2, Tuple p3);
    Triangle(Tuple p1, Tuple p2, Tuple p3, Tuple n1, Tuple n2, Tuple n3);

    Tuple p1() const;
    Tuple p2() const;
    Tuple p3() const;

    Tuple e1() const;
    Tuple e2() const;

    Tuple n1() const;
    Tuple n2() const;
    Tuple n3() const;

    Bounds bounds() const override;

private:
    Tuple _p1, _p2, _p3;
    Tuple _e1, _e2;
    Tuple _n1, _n2, _n3;

    std::vector<Intersection> local_intersect(const Ray& local_ray) const override;
    Tuple local_normal_at(const Tuple& local_point, const Intersection& intersection) const override;

};


