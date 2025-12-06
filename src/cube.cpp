#include "cube.hpp"

#include "glm/gtc/type_ptr.hpp"
#include "vao.hpp"
#include "vbo.hpp"

GLfloat cubeVertices[] = {
  // Positions           // Normales      // texture coordinate
  
  // front side
  -0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
   0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
   0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
  -0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 1.0f,

  // back side 
  -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    1.0f, 0.0f,
   0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    0.0f, 0.0f,
   0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    0.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    1.0f, 1.0f,

  // left side
  -0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,    1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,    0.0f, 1.0f,

  // right side
  0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
  0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
  0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 1.0f,
  0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     1.0f, 1.0f,

  // bottom side
  -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,    0.0f, 1.0f,
   0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,    1.0f, 1.0f, 
   0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,    1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,    0.0f, 0.0f,

  // up side
  -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,     0.0f, 1.0f,
   0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,     1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,     1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,     0.0f, 0.0f,
};

unsigned int cubeIndices[] = {
  0, 1, 2,   // Triangle 1
  2, 3, 0,   // Triangle 2

  4, 5, 6,   // Triangle 3
  6, 7, 4,   // Triangle 4

  8, 9, 10,  // Triangle 5
  10, 11, 8, // Triangle 6

  12, 13, 14, // Triangle 7
  14, 15, 12, // Triangle 8

  16, 17, 18, // Triangle 9
  18, 19, 16, // Triangle 10

  20, 21, 22, // Triangle 11
  22, 23, 20  // Triangle 12
};

const char* cubeVertexShader = R"(
    #version 330 core

    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aNormal;
    layout (location = 2) in vec2 aTexCoords;

    uniform mat4 projection;
    uniform mat4 model;
    uniform mat4 view;

    out vec3 Normal;
    out vec3 FragPos;
    out vec2 TexCoords;

    void main() {
        FragPos = vec3(model * vec4(aPos, 1.0));
        gl_Position = projection * view * vec4(FragPos, 1.0);
    
        Normal = mat3(transpose(inverse(model))) * aNormal;
        TexCoords = aTexCoords;
    }
)";

const char* cubeFragShader = R"(
    #version 330 core
    out vec4 FragColor;

    // Définitions de struct non utilisées pour l'éclairage mais laissées pour référence
    struct Material {
        sampler2D diffuse;
        vec3 specular;    
        float shininess;
    }; 
    struct Light {
        vec3 position;

        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };

    in vec3 FragPos;  
    in vec3 Normal;  
    in vec2 TexCoords;
    
    uniform vec3 viewPos;
    uniform Material material; // Utilisé uniquement pour material.diffuse
    uniform Light light;       // Non utilisé

    void main()
    {
        // 1. Lire la couleur de la texture
        vec4 texColor = texture(material.diffuse, TexCoords);

        // 2. Afficher la couleur de la texture directement
        FragColor = texColor; 
        
        // Toutes les lignes de calcul d'éclairage (ambient, diffuse, specular) sont retirées.
    }
)";

Cube::Cube(Camera& camera)
    : vbo(cubeVertices, sizeof(cubeVertices)),
      ebo(cubeIndices, sizeof(cubeIndices)),
      texture("stone.png"),
      camera(camera),
      shader(cubeVertexShader, cubeFragShader)
{
  vao.bind();
  vbo.bind();

  GLsizei stride = 8 * sizeof(float);

  vao.setAttributePointer(0, 3, GL_FLOAT, stride, (void*)0);
  vao.setAttributePointer(1, 3, GL_FLOAT, stride, (void*)(3 * sizeof(float)));
  vao.setAttributePointer(2, 2, GL_FLOAT, stride, (void*)(6 * sizeof(float)));

  ebo.bind();
}

void Cube::loop(int width, int height)
{
  shader.use();
  glActiveTexture(GL_TEXTURE0);

  glm::vec3 coordinate = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::mat4 projection = glm::perspective(
      glm::radians(camera.fov),
      static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

  GLint texLoc = glGetUniformLocation(shader.getProgram(), "material.diffuse");
  glUniform1i(texLoc, 0);

  GLint projectionLoc = glGetUniformLocation(shader.getProgram(), "projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

  GLint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE,
                     glm::value_ptr(camera.getViewMatrix()));

  glm::mat4 model = glm::translate(glm::mat4(1.0f), coordinate);
  GLint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

  vao.drawElement(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(unsigned int),
                  GL_UNSIGNED_INT, 0);
}