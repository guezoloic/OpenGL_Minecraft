#ifndef VBO_HPP
#define VBO_HPP

#include <stddef.h>

#include "glad/glad.h"

// A VBO (Vertex Buffer Object) is a contiguous block of GPU memory that stores
// vertex data as raw bytes.
class VBO
{
 private:
  GLuint id;  // OpenGL handle for this buffer

 public:
  // VBO constructor
  // It uploads raw vertex data into GPU memory (VRAM).
  // The interpretation of this data is defined later by the VAO.
  VBO(const void *data, size_t size);

  // VBO destructor
  // Deletes the GPU buffer when the VBO object goes out of scope. Frees the
  // VRAM associated with this VBO.
  ~VBO();

  // Binds this VBO to the current GL_ARRAY_BUFFER target
  void bind();

  // unbinds current GL_ARRAY_BUFFER target (it's replaced by null id)
  static void unbind();
};

#endif