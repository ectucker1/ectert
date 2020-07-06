#pragma once
#include <iostream>

class Tuple {

public:
	float x, y, z, w;

	Tuple(float x, float y, float z, float w);
	static Tuple point(float x, float y, float z);
	static Tuple vector(float x, float y, float z);

	bool is_point() const;
	bool is_vector() const;

	Tuple operator-() const;

	Tuple operator +(Tuple other) const;
    Tuple operator -(Tuple other) const;

    Tuple operator *(float scalar) const;
    Tuple operator /(float scalar) const;

    float magnitude_sq() const;
    float magnitude() const;

    Tuple normalized() const;

    float dot(Tuple other) const;
    Tuple cross(Tuple other) const;

    Tuple reflect(Tuple other) const;

    bool operator ==(Tuple other) const;

};

std::ostream& operator <<(std::ostream& stream, const Tuple& tuple);
