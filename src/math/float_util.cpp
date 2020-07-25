#include<cmath>

bool float_equal(float a, float b) {
	const float epsilon = 0.003f;
	return std::abs(a - b) < epsilon;
}
