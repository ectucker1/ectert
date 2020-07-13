#pragma once

class Shape;

#include <vector>
#include "shapes/shape.h"

class Intersection {

public:
    float t;
    const Shape* object;

    static const Intersection NIL;

    Intersection(float t, const Shape* object);

    bool operator ==(const Intersection& other) const;

    bool operator<(const Intersection& other) const;

};

std::vector<Intersection> sort_intersections(std::vector<Intersection>& values);

Intersection hit(std::vector<Intersection>& list);
