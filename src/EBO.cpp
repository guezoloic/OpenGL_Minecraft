#include "ebo.hpp"

EBO::EBO(unsigned int* indices, size_t size)
{
  glGenBuffers(1, &id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

EBO::~EBO() { glDeleteBuffers(1, &id); }

void EBO::bind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }

void EBO::unbind() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }