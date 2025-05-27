#ifndef BLOCK_H
#define BLOCK_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaderClass.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

class Block {
public:
	GLfloat vertices[288] = 
		{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
    // Front face
    -0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.0f, 1.0f, // Bottom-left
     0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.0f, 1.0f, // Bottom-right
     0.5f,  0.5f,  0.5f,     0.92f, 0.86f, 0.76f,	 1.0f, 1.0f,      0.0f, 0.0f, 1.0f, // Top-right
    -0.5f,  0.5f,  0.5f,     0.92f, 0.86f, 0.76f,	 0.0f, 1.0f,      0.0f, 0.0f, 1.0f, // Top-left
    
    // Back face
    -0.5f, -0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, 0.0f, -1.0f, // Bottom-right
     0.5f, -0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.0f, -1.0f, // Bottom-left
     0.5f,  0.5f, -0.5f,     0.92f, 0.86f, 0.76f,	 0.0f, 1.0f,      0.0f, 0.0f, -1.0f, // Top-left
    -0.5f,  0.5f, -0.5f,     0.92f, 0.86f, 0.76f,	 1.0f, 1.0f,      0.0f, 0.0f, -1.0f, // Top-right
    
    // Left face
    -0.5f, -0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      -1.0f, 0.0f, 0.0f, // Bottom-back
    -0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      -1.0f, 0.0f, 0.0f, // Bottom-front
    -0.5f,  0.5f,  0.5f,     0.92f, 0.86f, 0.76f,	 1.0f, 1.0f,      -1.0f, 0.0f, 0.0f, // Top-front
    -0.5f,  0.5f, -0.5f,     0.92f, 0.86f, 0.76f,	 0.0f, 1.0f,      -1.0f, 0.0f, 0.0f, // Top-back
    
    // Right face
     0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      1.0f, 0.0f, 0.0f, // Bottom-front
     0.5f, -0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      1.0f, 0.0f, 0.0f, // Bottom-back
     0.5f,  0.5f, -0.5f,     0.92f, 0.86f, 0.76f,	 1.0f, 1.0f,      1.0f, 0.0f, 0.0f, // Top-back
     0.5f,  0.5f,  0.5f,     0.92f, 0.86f, 0.76f,	 0.0f, 1.0f,      1.0f, 0.0f, 0.0f, // Top-front
    
    // Top face
    -0.5f,  0.5f,  0.5f,     0.92f, 0.86f, 0.76f,	 0.0f, 0.0f,      0.0f, 1.0f, 0.0f, // Front-left
     0.5f,  0.5f,  0.5f,     0.92f, 0.86f, 0.76f,	 1.0f, 0.0f,      0.0f, 1.0f, 0.0f, // Front-right
     0.5f,  0.5f, -0.5f,     0.92f, 0.86f, 0.76f,	 1.0f, 1.0f,      0.0f, 1.0f, 0.0f, // Back-right
    -0.5f,  0.5f, -0.5f,     0.92f, 0.86f, 0.76f,	 0.0f, 1.0f,      0.0f, 1.0f, 0.0f, // Back-left
    
    // Bottom face
    -0.5f, -0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Back-left
     0.5f, -0.5f, -0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Back-right
     0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	 1.0f, 1.0f,      0.0f, -1.0f, 0.0f, // Front-right
    -0.5f, -0.5f,  0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 1.0f,      0.0f, -1.0f, 0.0f  // Front-left
};

GLuint indices[36] =
{
    // Caras laterales (24 índices) - lados
    0, 1, 2, 2, 3, 0,     // Front face
    4, 5, 6, 6, 7, 4,     // Back face
    8, 9, 10, 10, 11, 8,  // Left face
    12, 13, 14, 14, 15, 12, // Right face
    
    // Cara superior (6 índices) - top
    16, 17, 18, 18, 19, 16,
    
    // Cara inferior (6 índices) - bottom
    20, 21, 22, 22, 23, 20
};
	
	Block();
    void loadTextures();
    void setupTextureUnits(Shader& shader);
    void draw(GLuint& shader);
    void deletes();

private:
	Texture block_side;
    Texture block_top;
    Texture block_bottom;
};

#endif

