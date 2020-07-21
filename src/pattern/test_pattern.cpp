#include "test_pattern.h"

TestPattern::TestPattern() = default;

Color TestPattern::sample_pattern(Tuple position) const {
    return Color(position.x, position.y, position.z);
}
