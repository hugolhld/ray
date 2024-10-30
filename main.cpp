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

    auto random_float = [](float min, float max) {
        return min + (max - min) * (float)rand() / RAND_MAX;
    };

    // Add objects to the scene
    // scene.addSphere(Sphere(Vector3D(0, 1, -5), 1.0f, Color(1, 0, 0)));
    scene.addPlane(Plane(Vector3D(0, 1, 0),      // Normal vers le haut
                        -1.0f,                     // Distance
                        Color(1.0f, 1.0f, 1.0f),  // Couleur 1 (blanc)
                        Color(0.1f, 0.1f, 0.1f),  // Couleur 2 (noir)
                        0.5f,                     // Réflectivité
                        1.0f));                   // Taille des cases

    // Camera setup
    Vector3D cameraPos(0, 0, 2);
    Vector3D cameraTarget(0, 0, 0);
    Vector3D cameraUp(0, 1, 0);

    Vector3D cameraDir = (cameraTarget - cameraPos).normalize();
    Vector3D cameraRight = cameraDir.cross(cameraUp).normalize();
    Vector3D cameraUpActual = cameraRight.cross(cameraDir).normalize();

     // Configuration de la grille
    const float SPHERE_SPACING = 1.0f;
    const float SPHERE_RADIUS = 0.4f;  // Rayon fixe pour toutes les sphères
    const int GRID_WIDTH = 5;          // 5 sphères en largeur
    const int GRID_HEIGHT = 3;         // 3 sphères en hauteur
    const int GRID_DEPTH = 2;          // 2 sphères en profondeur

    // Placer les sphères sur la grille
    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            for (int z = 0; z < GRID_DEPTH; z++) {
                // Calculer la position sur la grille
                float posX = (x - GRID_WIDTH/2.0f) * SPHERE_SPACING;
                float posY = y * SPHERE_SPACING;
                float posZ = 0.0f - (z * SPHERE_SPACING);  // Commence à z=-5 et va vers le fond

                // Créer une couleur aléatoire
                Color color(random_float(0.0f, 1.0f),
                          random_float(0.0f, 1.0f),
                          random_float(0.0f, 1.0f));

                // Ajouter la sphère à la scène
                scene.addSphere(Sphere(Vector3D(posX, posY, posZ), 
                                     SPHERE_RADIUS, 
                                     color));
            }
        }
    }

    // Render the scene
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
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
    }

    image.WriteFile("test.png");
    return 0;
}