#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "game.hpp"

int main()
{
    Game game(800, 600, "game");

    auto quit = [](Game *g) {
      return !glfwWindowShouldClose(g->getWindow());
    };

    game.run(quit);
    return 0;
}