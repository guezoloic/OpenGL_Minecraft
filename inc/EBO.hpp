#ifndef EBO_HPP
#define EBO_HPP

#include <stddef.h>

#include "glad/glad.h"


class EBO
{
 private:
  GLuint id;

 public:
  EBO(unsigned int* indices, size_t size);
  ~EBO();

  void bind();
  void unbind();
};
#endif