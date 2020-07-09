#pragma once

class Sphere;

#include <vector>
#include "sphere.h"

class Intersection {

public:
    float t;
    const Sphere* object;

    static const Intersection NIL;

    Intersection(float t, const Sphere* object);

    bool operator ==(const Intersection& other) const;

    bool operator<(const Intersection& other) const;

};

std::vector<Intersection> sort_intersections(std::vector<Intersection>& values);

Intersection hit(std::vector<Intersection>& list);
