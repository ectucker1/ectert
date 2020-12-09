#pragma once

inline bool float_equal(float a, float b) {
    const float epsilon = 0.003f;
    // Or handles simple cases or infinity
    return a == b || std::abs(a - b) < epsilon;
}
