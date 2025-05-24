#ifndef TEXTURES_H
#define TEXTURES_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

// Declara IDs de texturas como extern (definidos en textures.cpp)
extern GLuint textureTop, textureSide, textureBottom;

// Función para cargar texturas
void loadTextures();

#endif
