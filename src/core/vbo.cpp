#include "core/vbo.hpp"

#include <cstddef>

VBO::VBO(const void *data, std::size_t size)
{
  // Generate a unique OpenGL buffer handle (ID).
  glGenBuffers(1, &id);
  // Binding the VBO is mandatory before allocating GPU memory
  bind();
  // Allocate GPU memory and upload data.
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VBO::~VBO()
{
  // delete the OpenGL buffer handle
  glDeleteBuffers(1, &this->id);
}

void VBO::bind()
{
  // Bind this buffer to the GL_ARRAY_BUFFER target.
  // GL_ARRAY_BUFFER tells opengl this buffer contains vertices
  glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VBO::unbind() 
{ 
  // bind the buffer to NULL handle (remove old id)
  glBindBuffer(GL_ARRAY_BUFFER, 0); 
}