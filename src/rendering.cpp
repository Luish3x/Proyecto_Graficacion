#include "../include/rendering.h"
#include "../include/textures.h"  // Para acceder a las texturas

void drawTexturedCube(float x, float y, float z) {
    float vertices[][3] = {
        {x,     y,     z    }, {x + 1, y,     z    }, 
        {x + 1, y + 1, z    }, {x,     y + 1, z    },
        {x,     y,     z + 1}, {x + 1, y,     z + 1}, 
        {x + 1, y + 1, z + 1}, {x,     y + 1, z + 1}
    };

    int faces[][4] = {
        {0, 1, 2, 3}, {5, 4, 7, 6}, {0, 4, 5, 1}, 
        {3, 2, 6, 7}, {4, 0, 3, 7}, {1, 5, 6, 2}
    };

    // Cara superior (top)
    glBindTexture(GL_TEXTURE_2D, textureTop);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[faces[3][0]]);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[faces[3][1]]);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[faces[3][2]]);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[faces[3][3]]);
    glEnd();
    
    // Caras laterales
    glBindTexture(GL_TEXTURE_2D, textureSide);
    for (int i : {0, 1, 4, 5}) {
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[faces[i][0]]);
            glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[faces[i][1]]);
            glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[faces[i][2]]);
            glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[faces[i][3]]);
        glEnd();
    }
    
    // Cara inferior (bottom)
    glBindTexture(GL_TEXTURE_2D, textureBottom);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[faces[2][0]]);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[faces[2][1]]);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[faces[2][2]]);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[faces[2][3]]);
    glEnd();
}

void terrain_gen(GLint x, GLint z) {
    for (size_t i = 0; i < x; i++) {
        for (size_t j = 0; j < z; j++) {
            drawTexturedCube(i, 0, j);
        }
    }
    for (size_t i = -x; i < 0; i++) {
        for (size_t j = -z; j < 0; j++) {
            drawTexturedCube(i, 0, j);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

	// Usa la cámara global
    gluLookAt(
        mainCamera.position.x, mainCamera.position.y, mainCamera.position.z,
        mainCamera.position.x + mainCamera.front.x,
        mainCamera.position.y + mainCamera.front.y,
        mainCamera.position.z + mainCamera.front.z,
        mainCamera.up.x, mainCamera.up.y, mainCamera.up.z
    );


    glEnable(GL_TEXTURE_2D);
    terrain_gen(128, 128);
    glDisable(GL_TEXTURE_2D);

    float white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);

	updateCameraRotation();

    glutSwapBuffers();
}
