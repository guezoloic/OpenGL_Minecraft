#include "game.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main()
{
    Game game(800, 600, "game");
    game.run();
    return 0;
}