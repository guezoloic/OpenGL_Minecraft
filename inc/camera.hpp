#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct GLFWwindow;

class Camera
{
 private:
  int screenWidth;
  int screenHeight;

  double mousePosX;
  double mousePosY;
  bool firstMouse = true;

  float cameraYaw;
  float cameraPitch;

  glm::vec3 cameraFront;
  glm::vec3 cameraUp;
  glm::vec3 cameraRight;
  glm::vec3 worldUp;

  GLFWwindow* window;

  void processInput(float deltaTime);
  void processMouseMovement();
  void updateCameraVectors();

 public:
  Camera(int width, int height, GLFWwindow* window, float sensitivity);

  void update(float deltaTime);
  glm::mat4 getViewMatrix();

  float speed;
  float cameraSensitivity;
  float fov;

  glm::vec3 cameraPosition;
};

#endif
