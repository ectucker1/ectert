#pragma once

#include "pattern.h"

class StripedPattern : public Pattern {

public:
    Color a;
    Color b;

    StripedPattern(Color a, Color b);

    Color sample_pattern(Tuple position) const override;

};
