#pragma once

#include "pattern.h"

class TestPattern : public Pattern {

public:
    TestPattern();

    Color sample_pattern(Tuple position) const override;

};
