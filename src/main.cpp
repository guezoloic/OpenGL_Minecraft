#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>

#include "camera.hpp"
#include "cube.hpp"

static void glfwErrorCallback(int error, const char *description)
{
  std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

int main()
{
  const char *title = "window";
  int width = 800, height = 600;

  glfwSetErrorCallback(glfwErrorCallback);

  if (glfwInit() == GLFW_FALSE)
  {
    std::cerr << "ERROR(GLFW): initialisation error" << std::endl;
    exit(EXIT_FAILURE);
  }

  // OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DEPTH_BITS, 24);
  glfwWindowHint(GLFW_STENCIL_BITS, 8);
  glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (window == nullptr)
  {
    std::cerr
        << "ERROR: Failed to create GLFW window with requested GL version."
        << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "ERROR: Failed to initialize GLAD" << std::endl;
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSwapInterval(1);

  Camera camera(width, height, window, 0.1f);
  Cube cube{camera};

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_MULTISAMPLE);

  double deltaTime = 0.f;
  double lastTime = glfwGetTime();
  while (!glfwWindowShouldClose(window))
  {
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.5f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    double currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    camera.update(deltaTime);
    cube.loop(width, height);

    glfwPollEvents();
    glfwSwapBuffers(window);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
      std::cerr << error << std::endl;
      // exit(1);
    }
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
