#pragma once

#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Color.hpp"

class Plane {
public:
    Vector3D normal;
    float distance;
    Color color1;
    Color color2;
    float reflectivity;
    float checkSize;

    Plane(const Vector3D& n, float d, const Color& col1, const Color& col2, float refl = 0.5f, float size = 1.0f) 
        : normal(n.normalize()), distance(d), color1(col1), color2(col2), 
          reflectivity(refl), checkSize(size) {}

    bool intersect(const Ray& ray, float& t) const {
        float denom = normal.dot(ray.direction);
        if (fabs(denom) > 1e-6) {
            Vector3D p0(normal.x * distance, normal.y * distance, normal.z * distance);
            t = (p0 - ray.origin).dot(normal) / denom;
            return t > 0;
        }
        return false;
    }

    Color getColorAt(const Vector3D& point) const {
        float x = floor(point.x / checkSize);
        float z = floor(point.z / checkSize);
        
        if (static_cast<int>(fabs(x + z)) % 2 == 0) {
            return color1;
        }
        return color2;
    }
};