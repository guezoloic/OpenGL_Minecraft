#include "shader.hpp"

Shader::Shader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  shaderProgram = glCreateProgram();

  addVertShader(vertexShaderSource);
  addFragShader(fragmentShaderSource);

  compileInProgram();
}

void Shader::addVertShader(const char* vertexShaderSource)
{
  glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
  glCompileShader(vertexShader);
}

void Shader::addFragShader(const char* fragmentShaderSource)
{
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);
}

void Shader::compileInProgram()
{
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDetachShader(shaderProgram, vertexShader);
  glDetachShader(shaderProgram, fragmentShader);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader() { glDeleteProgram(shaderProgram); }

void Shader::use() const { glUseProgram(shaderProgram); }

GLuint Shader::getProgram() const { return shaderProgram; }