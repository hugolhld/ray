#pragma once

#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"

class Sphere {
public:
    Vector3D center;
    float radius;
    Color color;

    Sphere(const Vector3D& c, float r, const Color& col) 
        : center(c), radius(r), color(col) {}

    bool intersect(const Ray& ray, float& t) const {
        Vector3D oc = ray.origin - center;
        float a = ray.direction.dot(ray.direction);
        float b = 2.0f * oc.dot(ray.direction);
        float c = oc.dot(oc) - radius * radius;
        float discriminant = b*b - 4*a*c;
        
        if (discriminant < 0) return false;
        
        t = (-b - sqrt(discriminant)) / (2.0f*a);
        return t > 0;
    }
};