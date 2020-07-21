#include "checker_pattern.h"

#include <cmath>

CheckerPattern::CheckerPattern(Color a, Color b) : a(a), b(b) {}

Color CheckerPattern::sample_pattern(Tuple position) const {
    if ((int) (floorf(position.x) + floorf(position.y) + floorf(position.z)) % 2 == 0) {
        return a;
    }
    return b;
}
