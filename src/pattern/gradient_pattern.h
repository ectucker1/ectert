#pragma once

#include "pattern.h"

class GradientPattern : public Pattern {

public:
    Color a;
    Color b;

    GradientPattern(Color a, Color b);

    Color sample_pattern(Tuple position) const override;

};
