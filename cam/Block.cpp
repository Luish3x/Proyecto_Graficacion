#include "../include/Block.h"
#include "../include/Texture.h"

Block::Block() {
    // Carga las texturas (ajusta las rutas según necesites)
    block_side = Texture("textures/grass_block_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    block_top = Texture("textures/grass_block_top.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    block_bottom = Texture("textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_RGBA, GL_UNSIGNED_BYTE);
}

void Block::loadTextures() {
    // Carga las texturas (ajusta las rutas según necesites)
    block_side = Texture("textures/grass_block_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    block_top = Texture("textures/grass_block_top.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
    block_bottom = Texture("textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_RGBA, GL_UNSIGNED_BYTE);
}

void Block::setupTextureUnits(Shader& shader) {
    block_side.texUnit(shader, "texSide", 0);
    block_top.texUnit(shader, "texTop", 1);
    block_bottom.texUnit(shader, "texBottom", 2);
}

void Block::draw(GLuint& shaderID) {
    // Bind de texturas y dibujo del bloque
	glActiveTexture(GL_TEXTURE0);
    block_side.Bind();
	glUniform1i(glGetUniformLocation(shaderID, "faceID"), 0); // Cara lateral
	glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0); // Primeros 24 índices (lados)

	glActiveTexture(GL_TEXTURE1);
    block_top.Bind();
	glUniform1i(glGetUniformLocation(shaderID, "faceID"), 1); // Cara superior
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(GLuint))); // Siguientes 6 índices

	// Dibuja la PARTE INFERIOR (faceID = 2)

	glActiveTexture(GL_TEXTURE2);
	block_bottom.Bind();
	glUniform1i(glGetUniformLocation(shaderID, "faceID"), 2); // Cara inferior
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(GLuint))); // Últimos 6 índices

    // Aquí iría el código para dibujar tu VAO/VBO/EBO
    // glDrawElements(...);
}

void Block::deletes(){
	block_top.Delete();
	block_side.Delete();
	block_bottom.Delete();
}
