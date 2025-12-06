#ifndef VAO_HPP
#define VAO_HPP

#include <stddef.h>

#include "glad/glad.h"

class VAO
{
 private:
  unsigned int id;

 public:
  VAO();
  ~VAO();

  void bind();
  void unbind();

  void setAttributePointer(GLuint index, GLuint size, GLenum type,
                           GLsizei stride, const void* offset);
  void drawElement(GLenum mode, GLsizei count, GLenum type,
                   const void* indices);
  void drawArray(GLenum mode, GLint first, GLsizei count);
};

#endif