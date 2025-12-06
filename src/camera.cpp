#include "camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Camera::Camera(int width, int height, GLFWwindow* window, float sensitivity)
    : screenWidth(width),
      screenHeight(height),
      window(window),
      cameraYaw(-90.0f),
      cameraPitch(10.0f),
      speed(3.0f),
      cameraSensitivity(sensitivity),
      fov(45.0f),
      cameraPosition(0.0f, 0.0f, 0.0f),
      cameraFront(0.0f, 0.0f, -1.0f),
      worldUp(0.0f, 1.0f, 0.0f),
      firstMouse(true)
{
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  updateCameraVectors();
}

void Camera::update(float deltaTime)
{
  processInput(deltaTime);
  processMouseMovement();
  updateCameraVectors();
}

void Camera::processInput(float deltaTime)
{
  float velocity = speed * deltaTime;

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraPosition += cameraFront * velocity;

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraPosition -= cameraFront * velocity;

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraPosition += cameraRight * velocity;

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraPosition -= cameraRight * velocity;

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    cameraPosition += cameraUp * velocity;

  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    cameraPosition -= cameraUp * velocity;

  // Zoom
  fov = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            ? 35.f
            : 45.f;
}

void Camera::processMouseMovement()
{
  double mouseX, mouseY;
  glfwGetCursorPos(window, &mouseX, &mouseY);

  if (firstMouse)
  {
    mousePosX = mouseX;
    mousePosY = mouseY;
    firstMouse = false;
    return;
  }

  float deltaX = static_cast<float>(mouseX - mousePosX);
  float deltaY = static_cast<float>(mousePosY - mouseY);

  mousePosX = mouseX;
  mousePosY = mouseY;

  deltaX *= cameraSensitivity;
  deltaY *= cameraSensitivity;

  cameraYaw += deltaX;
  cameraPitch += deltaY;

  if (cameraPitch > 89.0f) cameraPitch = 89.0f;
  if (cameraPitch < -89.0f) cameraPitch = -89.0f;
}

void Camera::updateCameraVectors()
{
  glm::vec3 front;
  front.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
  front.y = sin(glm::radians(cameraPitch));
  front.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
  cameraFront = glm::normalize(front);

  cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
  cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

glm::mat4 Camera::getViewMatrix()
{
  return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}
