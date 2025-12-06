#ifndef CUBE_HPP
#define CUBE_HPP

#include <stddef.h>

#include "camera.hpp"
#include "ebo.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vao.hpp"
#include "vbo.hpp"

class Cube
{
 private:
  VBO vbo;
  EBO ebo;
  VAO vao;

  Camera &camera;
  Shader shader;
  Texture texture;

 public:
  Cube(Camera &camera);
  void loop(int width, int height);
};

#endif