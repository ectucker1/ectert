#include "scatter.h"

Scatter::Scatter(const Ray &scattered, const Color &attenuation, const bool &absorbed)
    : scattered(scattered), attenuation(attenuation), absorbed(absorbed) {}
