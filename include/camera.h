#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    float yaw, pitch;
    float sensitivity;

    Camera();

    void updateVectors();
	void moveCameraXZ(Camera& camera, float forwardSpeed, float strafeSpeed);
	void moveCameraY(Camera& camera, float verticalSpeed);
    void processMouseMovement(float xoffset, float yoffset);
    void processKeyboard(unsigned char key, float deltaTime);
    void processSpecialKeys(int key, float deltaTime);
};

// Funciones globales para callbacks
void mouseMove(int x, int y);
void updateCameraRotation();
void pressKey(unsigned char key, int xx, int yy);
void keyFnc(int key, int xx, int yy);

extern Camera mainCamera; // Instancia global accesible

#endif
