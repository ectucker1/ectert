#include "material.h"

#include <cmath>

Material::Material() {
    pattern = nullptr;
    color = Color(1, 1, 1);
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200.0;
    reflectivity = 0.0;
    alpha = 1.0;
    ior = 1.0;
}

bool Material::operator==(const Material &other) const {
    return color == other.color && ambient == other.ambient && diffuse == other.diffuse
        && specular == other.specular && shininess == other.shininess;
}

Color Material::lighting(const std::shared_ptr<const Shape>& shape, const PointLight &light, const Tuple &position, const Tuple &eyev, const Tuple &normal, bool in_shadow) const {
    // Phong reflection model

    // Choose pattern or base color
    Color sampleColor;
    if (pattern == nullptr) {
        sampleColor = color;
    } else {
        sampleColor = pattern->sample_shape(shape, position);
    }

    // Combine surface and light color
    Color effectiveColor = sampleColor * light.intensity;

    // Direction to light source
    Tuple lightv = (light.position - position).normalized();

    // Ambient contribution
    Color ambientColor = effectiveColor * ambient;

    Color diffuseColor = Color();
    Color specularColor = Color();

    // Don't include specular and diffuse if not in shadow
    if (!in_shadow) {
        // Cosine of angle between light and normal vector
        // Negative number means light is on other side
        float lightDotNormal = lightv.dot(normal);
        if (lightDotNormal >= 0) {
            // Diffuse contribution
            diffuseColor = effectiveColor * diffuse * lightDotNormal;

            Tuple reflectv = (-lightv).reflect(normal);
            // Cosine of angle between reflection and eye vector
            // Negative number means reflection away from eye
            float reflectDotEye = reflectv.dot(eyev);

            if (reflectDotEye <= 0) {
                specularColor = Color();
            } else {
                float factor = std::pow(reflectDotEye, shininess);
                specularColor = light.intensity * specular * factor;
            }
        }
    }

    return ambientColor + diffuseColor + specularColor;
}
