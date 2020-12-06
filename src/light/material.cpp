#include "material.h"

Material::Material() {
    ior = 1.0;
}

Color Material::emitted(const Hit &hit) const {
    return Color();
}

bool Material::operator==(const Material &other) const {
    return ior == other.ior;
}
