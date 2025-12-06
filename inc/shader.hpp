#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"

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