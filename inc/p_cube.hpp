#include "GLFW/glfw3.h"

constexpr GLfloat P_CUBE_VERTICE[] = {
  // Positions           // normales         // texture coordinate
  // front side
  -0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 0.0f,
   0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f,     1.0f, 0.0f,
   0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
  -0.5f,  0.5f, 0.5f,    0.0f, 0.0f, 1.0f,     0.0f, 1.0f,

  // back side 
  -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    1.0f, 0.0f,
   0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    0.0f, 0.0f,
   0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    0.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,    1.0f, 1.0f,

  // left side
  -0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,    0.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,    1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
  -0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,    0.0f, 1.0f,

  // right side
  0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     1.0f, 0.0f,
  0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
  0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,     0.0f, 1.0f,
  0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,     1.0f, 1.0f,

  // bottom side
  -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,    0.0f, 1.0f,
   0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,    1.0f, 1.0f, 
   0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,    1.0f, 0.0f,
  -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0f,    0.0f, 0.0f,

  // up side
  -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,     0.0f, 1.0f,
   0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,     1.0f, 1.0f,
   0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,     1.0f, 0.0f,
  -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f,     0.0f, 0.0f,
};

constexpr unsigned int P_CUBE_INDICE[] = {
  0, 1, 2,      // 1
  2, 3, 0,      // 2

  4, 5, 6,      // 3
  6, 7, 4,      // 4

  8, 9, 10,     // 5
  10, 11, 8,    // 6

  12, 13, 14,   // 7
  14, 15, 12,   // 8

  16, 17, 18,   // 9
  18, 19, 16,   // 10

  20, 21, 22,   // 11
  22, 23, 20    // 12
};  

extern "C" const unsigned char P_CUBE_FRAG[];
extern "C" const unsigned int P_CUBE_FRAG_LEN;
extern "C" const unsigned char P_CUBE_VERT[];
extern "C" const unsigned int P_CUBE_VERT_LEN;