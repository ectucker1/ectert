#include "material.h"

#include <cmath>

Material::Material() {
    color = Color(1, 1, 1);
    ambient = 0.1;
    diffuse = 0.9;
    specular = 0.9;
    shininess = 200.0;
}

bool Material::operator==(const Material &other) const {
    return color == other.color && ambient == other.ambient && diffuse == other.diffuse
        && specular == other.specular && shininess == other.shininess;
}

Color Material::lighting(const PointLight &light, const Tuple &position, const Tuple &eyev, const Tuple &normal) const {
    // Phong reflection model

    // Combine surface and light color
    Color effectiveColor = color * light.intensity;

    // Direction to light source
    Tuple lightv = (light.position - position).normalized();

    // Ambient contribution
    Color ambientColor = effectiveColor * ambient;

    Color diffuseColor;
    Color specularColor;

    // Cosine of angle between light and normal vector
    // Negative number means light is on other side
    float lightDotNormal = lightv.dot(normal);
    if (lightDotNormal < 0) {
        diffuseColor = Color();
        specularColor = Color();
    } else {
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

    return ambientColor + diffuseColor + specularColor;
}
