#ifndef VAO_HPP
#define VAO_HPP

#include <stddef.h>

#include "glad/glad.h"
namespace core
{
class VAO
{
 private:
  GLuint id;

 public:
  // Generates a new Vertex Array Object on the GPU
  VAO();
  // Deletes the VAO from GPU memory
  ~VAO();

  // Bind this VAO as the current active vertex array
  // All subsequent vertex attribute calls will affect this VAO
  void bind();
  // Unbind the VAO (bind VAO 0)
  // This prevents accidental modification of the currently bound VAO
  void unbind();

  // Define how vertex data is interpreted by OpenGL
  void setAttributePointer(GLuint index, GLuint size, GLenum type,
                           GLsizei stride, const void *offset);
  // Draw elements using the currently bound EBO (Element Buffer Object)
  void drawElement(GLenum mode, GLsizei count, GLenum type,
                   const void *indices);
  // Draw arrays directly from the VBOs (no EBO required)
  void drawArray(GLenum mode, GLint first, GLsizei count);
};
}  // namespace core

#endif