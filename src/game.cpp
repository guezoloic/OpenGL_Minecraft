#include "GL/glew.h"
#include "game.hpp"
#include "GLFW/glfw3.h"
#include <cstdlib>
#include <iostream>


Game::Game(int width, int height, string name) : 
  width(width), 
  height(height), 
  name(name.c_str())
{
  if(glfwInit() == GLFW_FALSE)
    std::cerr << "error glfw" << std::endl;
  
  this->window = glfwCreateWindow(
    this->width,
    this->height,
    this->name, 
    nullptr, 
    nullptr
  );

  // OpenGL 3.3
  glfwWindowHint(GLFW_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_VERSION_MINOR, 3);
  
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_STENCIL_BITS, 8);

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwMakeContextCurrent(this->window);

  glewInit();

  glEnable(GL_DEPTH_TEST); 
  glEnable(GL_MULTISAMPLE);
}

void Game::run(bool (*func)(Game *g))
{
  while(func(this))
  {
    glfwGetWindowSize(this->window, &this->width, &this->height);
    glViewport(0, 0, this->width, this->height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.5f, 0.2f, 0.2f, 1.0f);

    glDisable(GL_MULTISAMPLE);
    glfwPollEvents();
    glfwSwapBuffers(this->window);

    GLenum error = glGetError();
    if (error != glGetError())
    {
      std::cerr << error << std::endl;
      exit(1);
    }
  }
}

Game::~Game()
{
  glfwTerminate();
}

GLFWwindow *Game::getWindow()
{
  return this->window;
}
const char *Game::getName()
{
  return this->name;
}

int Game::getWidth()
{
  return this->height;
}

int Game::getHeight()
{
  return this->width;
}
