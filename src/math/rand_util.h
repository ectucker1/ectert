#pragma once

#include <random>
#include "tuple.h"

inline float random_float() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::minstd_rand generator;
    return distribution(generator);
}

inline float random_range(float min, float max) {
    // Returns a random real in [min, max)
    return min + (max - min) * random_float();
}

inline Tuple random_vector() {
    return Tuple::vector(random_float(), random_float(), random_float());
}

inline Tuple random_vector_range(float min, float max) {
    return Tuple::vector(random_range(min, max), random_range(min, max), random_range(min, max));
}

inline Tuple random_vector_in_unit_sphere() {
    // Try new vectors until one is found in the sphere
    while (true) {
        Tuple result = random_vector_range(-1.0f, 1.0f);
        if (result.magnitude_sq() < 1.0f)
            return result;
    }
}

inline Tuple random_unit_vector() {
    return random_vector_in_unit_sphere().normalized();
}
