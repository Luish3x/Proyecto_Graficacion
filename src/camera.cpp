#include "../include/camera.h"
#include <cmath>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <iostream>

Camera mainCamera; // Definición de la instancia global

const int EDGE_THRESHOLD = 50; // Distancia en píxeles desde el borde para activar la rotación
float autoRotationSpeed = 0.0f; // Velocidad de rotación automática

Camera::Camera() : 
    position(-10.0f, 4.0f, -10.0f),
    front(0.0f, 0.0f, 0.0f),
    right(1.0f, 0.0f, 0.0f),
    up(0.0f, 1.0f, 0.0f),
    yaw(-90.0f),
    pitch(0.0f),
    sensitivity(0.1f) {}

void Camera::updateVectors() {
    // Calcula front basado en yaw/pitch
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateVectors();
}

void Camera::moveCameraXZ(Camera& camera, float fowartSpeed, float strafeSpeed){
	glm::vec3 frontXZ = glm::normalize(glm::vec3 (camera.front[0], 0.0f, camera.front[2]));
	camera.position += frontXZ * fowartSpeed;

	glm::vec3 rightXZ = glm::normalize(glm::vec3 (camera.right[0], 0.0f, camera.right[2]));
	camera.position += rightXZ * strafeSpeed;
}

void Camera::moveCameraY(Camera& camera, float verticalSpeed){
	camera.position[1] += verticalSpeed;
}

void Camera::processKeyboard(unsigned char key, float deltaTime) {
    float velocity = 2.5f * deltaTime;
    switch (key) {
        case 'w': case 'W':
			moveCameraXZ(mainCamera, 0.1f, 0.0f);
            break;
        case 's': case 'S':
			moveCameraXZ(mainCamera, -0.1f, 0.0f);
            break;
        case 'a': case 'A':
			moveCameraXZ(mainCamera, 0.0f, -0.1f);
            break;
        case 'd': case 'D':
			moveCameraXZ(mainCamera, 0.0f, 0.1f);
            break;
        case ' ':
			moveCameraY(mainCamera, 0.1f);
            break;
    }
}

void Camera::processSpecialKeys(int key, float deltaTime) {
    float velocity = 2.5f * deltaTime;
	switch (key) {
		case GLUT_KEY_SHIFT_L:
			moveCameraY(mainCamera, -0.1f);
		default:
			break;
	}
}

// Callbacks globales
float lastX = 400, lastY = 300;
bool firstMouse = true;

void mouseMove(int x, int y) {
    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    if (x <= EDGE_THRESHOLD) {
		autoRotationSpeed = -1.0f;
		std::cout << x << std::endl;
	}
	else {
		autoRotationSpeed = 0.0f;
	}

	// Si no está rotando automáticamente, procesar el movimiento normal
    if (autoRotationSpeed == 0.0f) {
        float xoffset = x - lastX;
        float yoffset = lastY - y; // Invertido
        lastX = x;
        lastY = y;

        mainCamera.processMouseMovement(xoffset, yoffset);
    }
	//else {
    //    mainCamera.processMouseMovement(autoRotationSpeed, 0);
	//}

    glutPostRedisplay();
}

void updateCameraRotation() {
    if (autoRotationSpeed != 0.0f) {
        mainCamera.processMouseMovement(autoRotationSpeed, 0);
    }
}

void pressKey(unsigned char key, int xx, int yy) {
    mainCamera.processKeyboard(key, 0.016f); // ~60 FPS
    glutPostRedisplay();
    if (key == 27) exit(0); // Escape
}

void keyFnc(int key, int xx, int yy) {
    mainCamera.processSpecialKeys(key, 0.016f);
    glutPostRedisplay();
}
