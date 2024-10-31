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

    auto start = std::chrono::high_resolution_clock::now();

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float u = (2.0f * x / width - 1.0f) * aspect;
            float v = -(2.0f * y / height - 1.0f);

            Ray ray(cameraPos, Vector3D(u, v, -1).normalize());
            Color pixelColor = scene.trace(ray);
            image.SetPixel(x, y, pixelColor);
        }
        // Log time passed
        auto current = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current - start);
        std::cout << "\rTime passed: " << duration.count() / 1000.0f << " seconds and " << (y * 100 / height) << "% done" << std::flush;
    }

    // end the timer of the rendering
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "\nRendering time: " << duration.count() / 1000.0f << " seconds" << std::endl;

    image.WriteFile("test.png");
    std::cout << "\nRendering: 100%" << std::endl;
    return 0;
}