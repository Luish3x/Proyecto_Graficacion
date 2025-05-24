#ifndef RENDERING_H
#define RENDERING_H

#include <GL/gl.h>
#include <initializer_list>
#include "camera.h" // Añadir esta línea

void drawTexturedCube(float x, float y, float z);
void terrain_gen(GLint x, GLint z);
void display();

#endif
