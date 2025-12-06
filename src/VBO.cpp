#include "vbo.hpp"

VBO::VBO(GLfloat* vertices, size_t size)
{
  glGenBuffers(1, &id);
  glBindBuffer(GL_ARRAY_BUFFER, id);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO() { glDeleteBuffers(1, &id); }

void VBO::bind() { glBindBuffer(GL_ARRAY_BUFFER, id); }

void VBO::unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }