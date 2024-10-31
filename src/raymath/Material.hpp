#pragma once

#include "Color.hpp"

class Material {
public:
    Color color;
    float metallic;
    float roughness;
    float specular;

    Material(const Color& c, float m, float r, float s)
        : color(c), metallic(m), roughness(r), specular(s) {}
};
