#ifndef SHADER_HPP
#define SHADER_HPP

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;

    void addVertShader(const char* vertexShaderSource);
    void addFragShader(const char* fragmentShaderSource);
    void compileInProgram();

public:
    Shader(const char* vertexShaderSource, const char* fragmentShaderSource);             
    ~Shader();
    
    GLuint getProgram() const;
    void use() const;
};

#endif