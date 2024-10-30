#include <iostream>
#include "Color.hpp"
#include "Image.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Scene.hpp"

using namespace std;

int main()
{
    const int width = 1920;
    const int height = 1080;
    const float aspect = float(width) / float(height);

    Image image(width, height);
    Scene scene;

    auto random_float = [](float min, float max)
    {
        return min + (max - min) * (float)rand() / RAND_MAX;
    };

    scene.addPlane(Plane(Vector3D(0, 1, 0),
                         -1.0f,
                         Color(1.0f, 1.0f, 1.0f),
                         Color(0.1f, 0.1f, 0.1f),
                         0.5f,
                         1.0f));

    Vector3D cameraPos(0, 0, 2);
    Vector3D cameraTarget(0, 0, -4);
    Vector3D cameraUp(0, 1, 0);

    Vector3D cameraDir = (cameraTarget - cameraPos).normalize();
    Vector3D cameraRight = cameraDir.cross(cameraUp).normalize();
    Vector3D cameraUpActual = cameraRight.cross(cameraDir).normalize();

    const float SPHERE_SPACING = 1.0f;
    const float SPHERE_RADIUS = 0.4f;
    const int GRID_WIDTH = 7;
    const int GRID_DEPTH = 7;

    for (int x = 0; x < GRID_WIDTH; x++)
    {
        for (int z = 0; z < GRID_DEPTH; z++)
        {
            float posX = (x - GRID_WIDTH / 2.0f) * SPHERE_SPACING;
            float posY = random_float(0.0f, 1.0f);
            float posZ = 0.0f - (z * SPHERE_SPACING);

            Color color(random_float(0.0f, 1.0f),
                        random_float(0.0f, 1.0f),
                        random_float(0.0f, 1.0f));

            scene.addSphere(Sphere(Vector3D(posX, posY, posZ),
                                   SPHERE_RADIUS,
                                   color));
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float u = (2.0f * x / width - 1.0f) * aspect;
            float v = -(2.0f * y / height - 1.0f);

            Vector3D direction = (cameraDir +
                                  cameraRight * u +
                                  cameraUpActual * v)
                                     .normalize();

            Ray ray(cameraPos, direction);
            Color pixelColor = scene.trace(ray);
            image.SetPixel(x, y, pixelColor);
        }
        std::cout << "\rRendering: " << (y * 100 / height) << "%" << std::flush;
    }

    image.WriteFile("test.png");
    std::cout << "\nRendering: 100%" << std::endl;
    return 0;
}