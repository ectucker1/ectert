#include "point_light.h"

const PointLight PointLight::NIL = PointLight(Tuple::point(0, 0, 0), Color());

PointLight::PointLight(Tuple position, Color intensity) : position(position), intensity(intensity) {}

bool PointLight::operator==(const PointLight& other) const {
    return position == other.position && intensity == other.intensity;
}
