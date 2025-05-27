#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;

// Texturas para cada parte del cubo
uniform sampler2D texSide;  // Lados (GL_TEXTURE0)
uniform sampler2D texTop;   // Parte superior (GL_TEXTURE1)
uniform sampler2D texBottom;// Parte inferior (GL_TEXTURE2)

// Identificador de cara (0=lados, 1=arriba, 2=abajo)
uniform int faceID;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    // Selección de textura basada en la cara
    vec4 texColor;
    if(faceID == 0) {
        texColor = texture(texSide, texCoord);
    } else if(faceID == 1) {
        texColor = texture(texTop, texCoord);
    } else {
        texColor = texture(texBottom, texCoord);
    }

    // Cálculos de iluminación (igual que antes)
    float ambient = 0.20f;
    
    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);
    
    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
    float specular = specAmount * specularLight;
    
    // Color final con la textura seleccionada
    FragColor = texColor * lightColor * (diffuse + ambient + specular);
	//FragColor = texColor;
}
