#pragma once

#include "math/color.h"
#include "intersection/ray.h"

class Scatter {

public:
    Ray scattered;
    Color attenuation;

    bool absorbed;

    Scatter(const Ray& scattered, const Color& attenuation, const bool& absorbed);

};
