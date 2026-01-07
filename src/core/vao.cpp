#include "core/vao.hpp"

core::VAO::VAO() { glGenVertexArrays(1, &id); }

core::VAO::~VAO() { glDeleteVertexArrays(1, &id); }

void core::VAO::bind() { glBindVertexArray(id); }

void core::VAO::unbind() { glBindVertexArray(0); }

void core::VAO::setAttributePointer(GLuint index, GLuint size, GLenum type,
                                    GLsizei stride, const void *offset)
{
  // Enable the attribute at the given index
  glEnableVertexAttribArray(index);

  // Define the layout of the vertex attribute
  glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
}

void core::VAO::drawElement(GLenum mode, GLsizei count, GLenum type,
                            const void *indices)
{
  glDrawElements(mode, count, type, indices);
}

void core::VAO::drawArray(GLenum mode, GLint first, GLsizei count)
{
  glDrawArrays(mode, first, count);
}