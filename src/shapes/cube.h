#pragma once

#include "shape.h"

class Cube : public Shape {

public:
    Cube();
    Cube(const Matrix& transform);

    bool operator ==(const Cube& other) const;

private:
    std::vector<Intersection> local_intersect(const Ray& local_ray) const override;
    std::pair<float, float> check_axis(float origin, float direction) const;
    Tuple local_normal_at(const Tuple& local_point) const override;

};
