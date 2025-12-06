#include "vao.hpp"

VAO::VAO() { glGenVertexArrays(1, &id); }

VAO::~VAO() { glDeleteVertexArrays(1, &id); }

void VAO::bind() { glBindVertexArray(id); }

void VAO::unbind() { glBindVertexArray(0); }

void VAO::setAttributePointer(GLuint index, GLuint size, GLenum type,
                              GLsizei stride, const void* offset)
{
  bind();
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
}

void VAO::drawElement(GLenum mode, GLsizei count, GLenum type,
                      const void* indices)
{
  bind();
  glDrawElements(mode, count, type, indices);
}

void VAO::drawArray(GLenum mode, GLint first, GLsizei count)
{
  bind();
  glDrawArrays(mode, first, count);
}