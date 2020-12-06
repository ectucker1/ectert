#pragma once

#include "background.h"
#include "math/color.h"

class GradientBackground : public Background {
    Color start;
    Color end;

public:
    GradientBackground(const Color& start, const Color& end);

    virtual Color sample_background(const Ray& ray) const;

};
