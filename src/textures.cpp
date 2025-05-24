#include "../include/textures.h"
#include <stdio.h>

GLuint textureTop, textureSide, textureBottom;

void loadTextures() {
    textureTop = SOIL_load_OGL_texture(
        "textures/grass_block_top.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );
    
    textureSide = SOIL_load_OGL_texture(
        "textures/grass_block_side.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );
    
    textureBottom = SOIL_load_OGL_texture(
        "textures/dirt.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
    );

    if(!textureTop) printf("Error TOP: %s\n", SOIL_last_result());
    if(!textureSide) printf("Error SIDE: %s\n", SOIL_last_result());
    if(!textureBottom) printf("Error BOTTOM: %s\n", SOIL_last_result());

    // Configura parámetros de textura
    glBindTexture(GL_TEXTURE_2D, textureTop);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glBindTexture(GL_TEXTURE_2D, textureSide);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glBindTexture(GL_TEXTURE_2D, textureBottom);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
