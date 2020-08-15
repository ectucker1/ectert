#pragma once

class Ray;

#include <ostream>

class Bounds {

public:
    float minX, minY, minZ;
    float maxX, maxY, maxZ;

    Bounds(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);

    bool intersects(const Ray& local_ray) const;
    bool infinite() const;

    bool operator ==(const Bounds& other) const;

private:
    std::pair<float, float> check_axis(float origin, float direction, float min, float max) const;

};

std::ostream& operator <<(std::ostream& stream, const Bounds& bounds);
