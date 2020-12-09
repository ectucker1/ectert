#pragma once

class Shape;

#include <vector>
#include <memory>

class Intersection {

public:
    float t;
    std::shared_ptr<const Shape> object;
    float u;
    float v;

    static const Intersection NIL;

    Intersection(float t, std::shared_ptr<const Shape> object, float u = 0, float v = 0);

    bool operator ==(const Intersection& other) const;

    bool operator<(const Intersection& other) const;

};

std::vector<Intersection> sort_intersections(std::vector<Intersection>& values);

Intersection hit(const std::vector<Intersection>& list);
