#ifndef GAME_HPP
#define GAME_HPP

#include "GLFW/glfw3.h"
#include <string>

using namespace std;

class Game
{
private:
  int         width;
  int         height;
  const char *name;
  GLFWwindow *window;

public:
  Game(int width, int height, string name);
  ~Game();

  void run(bool (*func)(Game *g));

  GLFWwindow *getWindow();
  const char *getName();
  int getWidth();
  int getHeight();
};

#endif