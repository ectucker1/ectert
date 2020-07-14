#pragma once

class Shape;

#include "shapes/shape.h"
#include <vector>
#include <memory>

class Intersection {

public:
    float t;
    std::shared_ptr<const Shape> object;

    static const Intersection NIL;

    Intersection(float t, const std::shared_ptr<const Shape> object);

    bool operator ==(const Intersection& other) const;

    bool operator<(const Intersection& other) const;

};

std::vector<Intersection> sort_intersections(std::vector<Intersection>& values);

Intersection hit(std::vector<Intersection>& list);
