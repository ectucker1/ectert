#include "material.h"

Material::Material() {
    ior = 1.0;
}

bool Material::operator==(const Material &other) const {
    return ior == other.ior;
}
