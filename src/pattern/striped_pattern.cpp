#include "striped_pattern.h"
#include "shapes/shape.h"
#include <cmath>

StripedPattern::StripedPattern(Color a, Color b) : a(a), b(b) {}

Color StripedPattern::sample_pattern(Tuple position) const {
    if ((int) floorf(position.x) % 2 == 0) {
        return a;
    }
    return b;
}
