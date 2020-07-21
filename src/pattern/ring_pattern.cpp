#include "ring_pattern.h"

#include <cmath>

RingPattern::RingPattern(Color a, Color b) : a(a), b(b) {}

Color RingPattern::sample_pattern(Tuple position) const {
    float dist = std::sqrt(position.x * position.x + position.z * position.z);
    if ((int) floorf(dist) % 2 == 0) {
        return a;
    } else {
        return b;
    }
}
