#pragma once

#include <vector>
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include "Color.hpp"

class Scene {
private:
    std::vector<Sphere> spheres;
    std::vector<Plane> planes;

public:
    Scene() {}

    void addSphere(const Sphere& sphere) {
        spheres.push_back(sphere);
    }

    void addPlane(const Plane& plane) {
        planes.push_back(plane);
    }

    Color trace(const Ray &ray, int depth = 0) const {
        const int MAX_DEPTH = 5;
        if (depth >= MAX_DEPTH) return Color(0, 0, 0);

        float closest_t = INFINITY;
        Vector3D normal;
        Vector3D hitPoint;
        Color surfaceColor;
        float reflectivity = 0;

        for (const auto& sphere : spheres) {
            float t;
            if (sphere.intersect(ray, t) && t < closest_t) {
                closest_t = t;
                hitPoint = ray.pointAt(t);
                normal = (hitPoint - sphere.center).normalize();
                surfaceColor = sphere.color;
                reflectivity = 0.3f;
            }
        }

        for (const auto& plane : planes) {
            float t;
            if (plane.intersect(ray, t) && t < closest_t) {
                closest_t = t;
                hitPoint = ray.pointAt(t);
                normal = plane.normal;
                surfaceColor = plane.getColorAt(hitPoint);
                reflectivity = plane.reflectivity;
            }
        }

        if (closest_t < INFINITY) {
            Vector3D lightDir(0, -1, -1);
            lightDir = lightDir.normalize();

            float diffuse = -normal.dot(lightDir);
            if (diffuse < 0) diffuse = 0;

            Color reflectedColor(0, 0, 0);
            if (reflectivity > 0 && depth < MAX_DEPTH) {
                Vector3D reflectDir = ray.direction - normal * (2 * ray.direction.dot(normal));
                Ray reflectRay(hitPoint + normal * 0.001f, reflectDir);
                reflectedColor = trace(reflectRay, depth + 1);
            }

            return surfaceColor * diffuse * (1 - reflectivity) + reflectedColor * reflectivity;
        }

        return Color(0, 0, 0);
    }   
};