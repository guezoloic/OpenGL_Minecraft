#ifndef VBO_HPP
#define VBO_HPP

#include <stddef.h>

#include "glad/glad.h"

class VBO
{
 private:
  unsigned int id;

 public:
  VBO(GLfloat* vertices, size_t size);
  ~VBO();

  void bind();
  void unbind();
};

#endif