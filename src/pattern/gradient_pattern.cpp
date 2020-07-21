#include "gradient_pattern.h"

#include <cmath>

GradientPattern::GradientPattern(Color a, Color b) : a(a), b(b) {}

Color GradientPattern::sample_pattern(Tuple position) const {
    Color distance = b - a;
    float fraction = position.x - floorf(position.x);
    return a + distance * fraction;
}
