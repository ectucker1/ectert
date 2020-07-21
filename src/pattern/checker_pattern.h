#pragma once

#include "pattern.h"

class CheckerPattern : public Pattern {

public:
    Color a;
    Color b;

    CheckerPattern(Color a, Color b);

    Color sample_pattern(Tuple position) const override;

};
