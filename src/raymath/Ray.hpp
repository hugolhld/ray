#pragma once

#include "Vector3D.hpp"

class Ray {
public:
    Vector3D origin;
    Vector3D direction;

    Ray(const Vector3D& origin, const Vector3D& direction) 
        : origin(origin), direction(direction.normalize()) {}

    Vector3D pointAt(float t) const {
        return origin + direction * t;
    }
};