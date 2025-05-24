#include <cstdlib>
#define _CRT_SECURE_NO_WARNINGS
#include <GL/freeglut.h>
#include <math.h>
#include <glm/glm.hpp>

// Posición de la cámara
float x = 0.0f, y = 1.0f, z = 5.0f;

// Vectores de orientación (calculados con yaw/pitch)
glm::vec3 front(0.0f, 0.0f, -1.0f); // Apunta hacia -Z inicialmente
glm::vec3 right(1.0f, 0.0f, 0.0f);  // Derecha global (eje X)
glm::vec3 up(0.0f, 1.0f, 0.0f);     // Arriba global (eje Y)

// Ángulos de rotación (yaw: izquierda/derecha, pitch: arriba/abajo)
float yaw = -90.0f;   // Inicialmente mirando hacia -Z
float pitch = 0.0f;

// Sensibilidad del mouse
float sensitivity = 0.1f;

// Tamaño de la ventana
int ww, hh;

// Posición anterior del mouse (para rotación suave)
float lastX = 0.0f, lastY = 0.0f;
bool firstMouse = true;

// --- Funciones actualizadas ---

void mouseMove(int xx, int yy) {
    if (firstMouse) {
        lastX = xx;
        lastY = yy;
        firstMouse = false;
    }

    // Calcula el desplazamiento del mouse
    float xoffset = (xx - lastX) * sensitivity;
    float yoffset = (lastY - yy) * sensitivity; // Invertido para movimiento natural
    lastX = xx;
    lastY = yy;

    // Actualiza yaw y pitch
    yaw += xoffset;
    pitch += yoffset;

    // Limita el pitch para evitar "volteretas"
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Calcula los nuevos vectores de orientación
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    // Recalcula right y up
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));
}

void pressKey(unsigned char key, int xx, int yy) {
    float speed = 0.1f;

    switch (key) {
		case 'A':
		case 'a':
			x -= right.x * speed;
			z -= right.z * speed;
			break;
		case 'D':
		case 'd':
			x += right.x * speed;
			z += right.z * speed;
			break;
		case 'W':
		case 'w':
			x += front.x * speed;
			z += front.z * speed;
			break;
		case 'S':
		case 's':
			x -= front.x * speed;
			z -= front.z * speed;
			break;
		case 32: // Barra espaciadora (movimiento vertical)
			y += up.y * speed;
			break;
		case 27: // Escape
			exit(0);
			break;
		}
}

void keyFnc(GLint key, int xx, int yy){
    float speed = 0.1f;
	switch (key) {
		case  GLUT_KEY_SHIFT_L:
			y -= up.y * speed;
			break;
	}
}

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Usa gluLookAt con los vectores actualizados
    gluLookAt(
        x, y, z,                     // Posición de la cámara
        x + front.x, y + front.y, z + front.z,  // Punto de mira (eye + front)
        up.x, up.y, up.z              // Vector "arriba"
    );

    // Dibuja el cuadrado y el plano (igual que antes)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(-2.0, 2.0, -40.0);
    glVertex3f(2.0, 2.0, -40.0);
    glVertex3f(2.0, 6.0, -40.0);
    glVertex3f(-2.0, 6.0, -40.0);
    glEnd();

    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    glutSwapBuffers();
}

void resize(int w, int h) {

	// Setting ratio and new window size
	float ratio = w * 1.0 / h;
	ww = w;
	hh = h;

	// Setting the viewport
	glViewport(0, 0, w, h);

	// Setting the projection 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Resettign the modelview matrix 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Redisplay the scene
	glutPostRedisplay();

}

void update(int value) {

	// Timer function in which we redisplay the content of the screen each 1000/60 
	// msec, meaning that we want to achieve a 60fps configuration.
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, update, 0);
}

void setup(void) {

	// Clearing background color and setting up to black
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Other init procedures if needed

}

int main(int argc, char** argv) {

	// Init procedures
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1920, 1080);

	// Creating a window 
	glutCreateWindow("Camera.cpp");

	// Func callback
	glutReshapeFunc(resize);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(pressKey);
	glutSpecialFunc (keyFnc);
	glutPassiveMotionFunc(mouseMove);

	// here are the new entries
	glutTimerFunc(100, update, 0);

	// Setup func 
	setup();

	// start loop
	glutMainLoop();

	return 0;
}
