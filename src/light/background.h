#pragma once

#include <memory>

class Color;
class Ray;

class Background : public std::enable_shared_from_this<Background> {

public:
    virtual Color sample_background(const Ray& ray) const = 0;

};
