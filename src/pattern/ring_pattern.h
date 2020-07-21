#pragma once

#include "pattern.h"

class RingPattern : public Pattern {

public:
    Color a;
    Color b;

    RingPattern(Color a, Color b);

    Color sample_pattern(Tuple position) const override;

};
