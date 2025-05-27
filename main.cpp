#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include "glad/glad.h"
#include<GLFW/glfw3.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <iostream>
#include <ctime>

#include "Libraries/include/stb/stb_image.h"
#include"include/shaderClass.h"
#include"include/VAO.h"
#include"include/VBO.h"
#include"include/EBO.h"
#include"include/Texture.h"
#include"include/Camera.h"

const unsigned int width = 1920;
const unsigned int height = 1080;

// Vertices coordinates for a cube
GLfloat vertices[] =
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

GLuint indices[] =
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

GLfloat dis = 18.0f;
GLfloat lightVertices[] =
{ //     COORDINATES     //
    // Mover la luz 2 unidades en el eje X y 2 unidades en el eje Y
    -0.1f + dis-10, -0.1f+ dis,  0.1f + dis-10,  // 0
    -0.1f + dis-10, -0.1f+ dis, -0.1f + dis-10,  // 1
     0.1f + dis-10, -0.1f+ dis, -0.1f + dis-10,  // 2
     0.1f + dis-10, -0.1f+ dis,  0.1f + dis-10,  // 3
    -0.1f + dis-10,  0.1f+ dis,  0.1f + dis-10,  // 4
    -0.1f + dis-10,  0.1f+ dis, -0.1f + dis-10,  // 5
     0.1f + dis-10,  0.1f+ dis, -0.1f + dis-10,  // 6
     0.1f + dis-10,  0.1f+ dis,  0.1f + dis-10   // 7
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void DrawCube(Shader& shader, VAO& vao, Texture& side, Texture& top, Texture& bottom, const glm::mat4& model) {
    shader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
    vao.Bind();
    
    glActiveTexture(GL_TEXTURE0);
    side.Bind();
    glUniform1i(glGetUniformLocation(shader.ID, "faceID"), 0);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

    glActiveTexture(GL_TEXTURE1);
    top.Bind();
    glUniform1i(glGetUniformLocation(shader.ID, "faceID"), 1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(24 * sizeof(GLuint)));

    glActiveTexture(GL_TEXTURE2);
    bottom.Bind();
    glUniform1i(glGetUniformLocation(shader.ID, "faceID"), 2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(30 * sizeof(GLuint)));
}

using namespace std;


// Función para generar un heightmap con valores enteros
vector<vector<int>> generateDiamondSquareInt(int size, int roughness = 50, int initialVariation = 20, int precision = 10) {
    // Aseguramos que el tamaño sea 2^n + 1
    int actualSize = (1 << static_cast<int>(ceil(log2(size - 1)))) + 1;
    
    // Inicializamos la matriz con ceros
    vector<vector<int>> heightmap(actualSize, vector<int>(actualSize, 0));
    
    // Semilla aleatoria
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Inicializar las cuatro esquinas
    heightmap[0][0] = (rand() % (2 * initialVariation)) - initialVariation;
    heightmap[0][actualSize-1] = (rand() % (2 * initialVariation)) - initialVariation;
    heightmap[actualSize-1][0] = (rand() % (2 * initialVariation)) - initialVariation;
    heightmap[actualSize-1][actualSize-1] = (rand() % (2 * initialVariation)) - initialVariation;
    
    int variation = initialVariation;
    int step = actualSize - 1;
    
    while (step > 1) {
        // Fase Diamond
        for (int x = 0; x < actualSize - 1; x += step) {
            for (int y = 0; y < actualSize - 1; y += step) {
                int nextStep = step / 2;
                int midX = x + nextStep;
                int midY = y + nextStep;
                
                // El valor del centro es el promedio de las 4 esquinas más una variación aleatoria
                int average = (heightmap[x][y] + 
                             heightmap[x + step][y] + 
                             heightmap[x][y + step] + 
                             heightmap[x + step][y + step]) / 4;
                
                heightmap[midX][midY] = average + (rand() % (2 * variation)) - variation;
            }
        }
        
        // Fase Square
        for (int x = 0; x < actualSize - 1; x += step) {
            for (int y = 0; y < actualSize - 1; y += step) {
                int nextStep = step / 2;
                int midX = x + nextStep;
                int midY = y + nextStep;
                
                // Puntos en los bordes del cuadrado
                // Punto izquierdo
                if (x > 0) {
                    int average = (heightmap[x][y] + 
                                  heightmap[x][y + step] + 
                                  heightmap[midX][midY] + 
                                  heightmap[x - nextStep][midY]) / 4;
                    heightmap[x][midY] = average + (rand() % (2 * variation)) - variation;
                }
                
                // Punto superior
                if (y > 0) {
                    int average = (heightmap[x][y] + 
                                  heightmap[x + step][y] + 
                                  heightmap[midX][midY] + 
                                  heightmap[midX][y - nextStep]) / 4;
                    heightmap[midX][y] = average + (rand() % (2 * variation)) - variation;
                }
            }
        }
        
        // Reducimos el paso y la variación
        step /= 2;
        variation = (variation * roughness) / 100;
    }
    
    // Normalizar los valores si es necesario
    // Encontrar mínimos y máximos
    int min_val = heightmap[0][0];
    int max_val = heightmap[0][0];
    for (const auto& row : heightmap) {
        for (int val : row) {
            if (val < min_val) min_val = val;
            if (val > max_val) max_val = val;
        }
    }
    
    // Escalar si se desea (opcional)
    int range = max_val - min_val;
    if (range > 0) {
        for (auto& row : heightmap) {
            for (int& val : row) {
                val = ((val - min_val) * precision) / range;
            }
        }
    }
    
    // Si el tamaño pedido es menor que el calculado, recortamos la matriz
    if (size < actualSize) {
        heightmap.resize(size);
        for (auto& row : heightmap) {
            row.resize(size);
        }
    }
    
    return heightmap;
}


int main()
{
	// Initialize GLFW
    std::srand(std::time(0));
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", glfwGetPrimaryMonitor(), NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	glViewport(0, 0, width, height);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	// Shader for light cube
	Shader lightShader("shaders/light.vert", "shaders/light.frag");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

//	glm::vec3 cubo1 = glm::vec3(-1.0f, 0.0f, 0.0f);
//	glm::vec3 cubo2 = glm::vec3(0.0f, 0.0f, 0.0f);


	// Configuración del terreno
	const int TAM = 17;
    const int roughness = 3;


	vector<vector<int>> heightmap = generateDiamondSquareInt(TAM);

	// Estructura para almacenar las matrices de modelo de cada bloque
	//vector <vector< vector<glm::mat4>>> terreno(TAM, 
    //vector <vector< glm::mat4>>(TAM, 
    //vector <glm::mat4>(heightmap.size())));
	//vector<vector<vector<glm::mat4>>> terreno;
	vector<vector<vector<glm::mat4>>> terreno(TAM);

	for (int x = 0; x < TAM; ++x) {
		terreno[x].resize(TAM);
		for (int z = 0; z < TAM; ++z) {
			terreno[x][z].resize(heightmap[x][z]);  // ⬅️ Aquí está la clave
		}
	}

	// Generar las matrices de modelo para cada bloque
	for (int x = 0; x < TAM; x++) {
		for (int z = 0; z < TAM; z++) {
			for (int y = 0; y < heightmap[x][z]; y++) {
				// Posición del bloque (centrado en el origen)
				float posX = x - TAM/2.0f;
				float posY = y;  // Cada capa aumenta en Y
				float posZ = z - TAM/2.0f;
				
				terreno[x][z][y] = glm::mat4(1.0f);
				terreno[x][z][y] = glm::translate(terreno[x][z][y], glm::vec3(posX, posY, posZ));
			}
		}
	}



	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	// Texture

	Texture block_side("textures/grass_block_side.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture block_top("textures/grass_block_top.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_UNSIGNED_BYTE);
	Texture block_bottom("textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_RGBA, GL_UNSIGNED_BYTE);
	

	block_side.texUnit(shaderProgram, "texSide", 0);
	block_top.texUnit(shaderProgram, "texTop", 1);
	block_bottom.texUnit(shaderProgram, "texBottom", 2);

	//Block block(glm::vec3(0.0f, 0.0f, 0.0f), shaderProgram, block_side, block_top, block_bottom);


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(8.0f, 18.0f, 8.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{

		// Tiempo para movimiento suave
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		shaderProgram.Activate();
		camera.Matrix(shaderProgram, "camMatrix");
		//glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(cuboModel1));
			
		// Binds texture so that is appears in rendering
		//block_top.Bind();
		//block_side.Bind();
		//block_bottom.Bind();
		// Bind the VAO so OpenGL knows to use it
		//

		// Dibuja el bloque

		VAO1.Bind();

		for (int x = 0; x < TAM; x++) {
			for (int z = 0; z < TAM; z++) {
				for (int y = 0; y < heightmap[x][z]; y++) {
					DrawCube(shaderProgram, VAO1, block_side, block_top, block_bottom, terreno[x][z][y]);
				}
			}
		}




		// Tells OpenGL which Shader Program we want to use
		lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	block_top.Delete();
	block_side.Delete();
	block_bottom.Delete();


	shaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
