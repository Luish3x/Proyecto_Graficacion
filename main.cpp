#include <GL/glut.h>
#include "include/textures.h"
#include "include/rendering.h"
#include "include/init.h"
#include "include/camera.h" // Añadir al inicio

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(500, 10);
    glutInitWindowSize(1080, 720);
    glutCreateWindow("Mundo 3D con Cámara FPS");

	// Registra callbacks de cámara
    glutPassiveMotionFunc(mouseMove);
    glutKeyboardFunc(pressKey);
    glutSpecialFunc(keyFnc);
    glutTimerFunc(16, [](int) { glutPostRedisplay(); glutTimerFunc(16, [](int) {}, 0); }, 0);

    loadTextures();  // Desde textures.cpp
    init();          // Desde init.cpp

    glutDisplayFunc(display);   // Desde rendering.cpp
    glutReshapeFunc(reshape);   // Desde init.cpp

    glutMainLoop();
    return 0;
}
