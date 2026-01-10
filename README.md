# LearnOpenGL

## Why this project

This project was originally started a few years ago, back in high school. 
Its goal is to understand low-level programming and 3D rendering.
I chose **OpenGL** for its simplicity, flexibility, and cross-platform compatibility
Throughout this project, I implemented fundamental graphics concepts such as VAOs, VBOs, EBOs, and lighting calculations.

## Technologies Used

### OpenGL (Core Profile)

I primarilly chose **OpenGL** for its wide compatibility across platforms and GPUs. I simply wished this project to be built and see the magic happen. Most old graphic cards support OpenGL as standard API, and its much simpler for game development than **Vulkan**.

### GLFW

I also chose **GLFW** for its simplicity and cross-platform support. It handles window creation, OpenGL context management, and input (keyboard/mouse), It is allowing me to focus on graphics programming rather than writing platform specific code. 
GLFW is lightweight and works consistently on Windows, macOS, and Linux.

### GLAD

I chose **GLAD** to dynamically load OpenGL functions at runtime. Since OpenGL implementations differ between GPUs and OS, GLAD ensures that my code always calls the correct function pointers for the current platform and driver. It’s modern, header-only unlike **GLEW** which is much heavier than **GLAD**, and lets me select exactly which OpenGL version and extensions I need.

### GLM

I chose GLM because I didn’t want to implement all vector and matrix math from scratch. I already experimented with a custom SIMD-based math library, but GLM is more convenient, header-only, and highly optimized for graphics, letting me focus on rendering instead of low-level math.

### ImGui

I used **ImGui** as an optional GUI to debug and tweak rendering parameters in real time. It’s lightweight, immediate-mode, and lets me inspect and modify values without stopping the program.

### STB Image

I chose **stb_image** for image loading to easily handle textures. It’s header-only, simple to integrate, and supports common formats like PNG and JPEG without adding heavy dependencies.

## Triangle Rendering Example (OpenGL 4.1)

This example shows us how to render a simple 2D triangle using OpenGL (CORE 4.1) with GLFW, GLAD and a few core classes.

### Full Example

```cpp
#include "core/core.hpp"
#include "primitives/p_triangle.hpp"

int main()
{
  int width = 800, height = 600;
  const char *WINDOW_NAME = "window";

  glfwSetErrorCallback([](int error, const char *desc){ core::log::error(desc, error); });

  if (glfwInit() == GLFW_FALSE)
  {
    core::log::error("Failed to initialize GLFW.");
    std::exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DEPTH_BITS, 24);   
  glfwWindowHint(GLFW_STENCIL_BITS, 8);  
  glfwWindowHint(GLFW_SAMPLES, 4);       
#ifdef __APPLE__  
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(width, height, WINDOW_NAME, nullptr, nullptr);

  if (window == NULL)
  {
    core::log::error("Failed to create GLFW window.");
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    core::log::error("Failed to initialize GLAD.");
    glfwDestroyWindow(window);
    glfwTerminate();
    std::exit(EXIT_FAILURE);
  }

  glfwSwapInterval(1);  

  core::VAO vao{};
  core::VBO vbo{mesh::P_TRIANGLE_VERTICE, sizeof(mesh::P_TRIANGLE_VERTICE)};
  core::EBO ebo{mesh::P_TRIANGLE_INDICE, sizeof(mesh::P_TRIANGLE_INDICE)};

  core::Shader shader{(char *)mesh::P_TRIANGLE_VERT, (char *)mesh::P_TRIANGLE_FRAG};

  vao.bind();
  vbo.bind();
  ebo.bind();

  vao.setAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void *)(0));

  while (!glfwWindowShouldClose(window))
  {
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.5f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    vao.drawElement(GL_TRIANGLES, mesh::P_TRIANGLE_INDICE_LEN, GL_UNSIGNED_INT, 0);

    glfwPollEvents();
    glfwSwapBuffers(window);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
      core::log::error("", error);
      std::exit(EXIT_FAILURE);
    }
  }
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
```

# Breakdown

1. **Initialization window & OpenGL context**
   
   1. <u>Initialize GLFW and set an error callback</u>
   
   ```cpp
   glfwSetErrorCallback([](int error, const char *desc){
      // This anonymous function is called whenever GLFW encounters an error.
      core::log::error(desc, error);
   });
   
   // Initialize the GLFW library
   if (glfwInit() == GLFW_FALSE)
   {
    // If GLFW fails to initialize, log an error and terminate the program
    core::log::error("Failed to initialize GLFW.");
    std::exit(EXIT_FAILURE);
   }
   ```
   
   2. <u>Configure OpenGL version, profile and buffers</u>
   
   ```cpp
   // Set OpenGL version to 4.1 (major 4, minor 1)
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
   
   // Use the core profile (modern OpenGL, no deprecated features)
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
   // Request a 24-bit depth buffer for 3D depth calculations
   glfwWindowHint(GLFW_DEPTH_BITS, 24);
   
   // Request an 8-bit stencil buffer (useful for masking operations)
   glfwWindowHint(GLFW_STENCIL_BITS, 8);
   
   // Enable 4x multisampling (MSAA) for smoother edges 
   glfwWindowHint(GLFW_SAMPLES, 4);   
   
   // On macOS, forward compatibility is required to avoid deprecated features    
   #ifdef __APPLE__  
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   #endif
   ```
   
   3. <u>Create a window</u>
   
   ```cpp
   // Create a windowed mode window and its OpenGL context
   GLFWwindow *window = glfwCreateWindow(width, height, WINDOW_NAME, nullptr, nullptr);
   
   // Check if the window was successfully created
   if (window == NULL)
   {
   core::log::error("Failed to create GLFW window.");
   glfwTerminate(); // Clean up GLFW resources
   std::exit(EXIT_FAILURE);
   }
   
   // Make the OpenGL context of the window current on the calling thread
   glfwMakeContextCurrent(window);
   ```
   
   4. <u>Initialize GLAD for OpenGL function loading</u>
   
   ```cpp
   // GLAD manages OpenGL function pointers and extensions
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
    core::log::error("Failed to initialize GLAD.");
    glfwDestroyWindow(window); // Destroy window before exiting
    glfwTerminate();           // Terminate GLFW
    std::exit(EXIT_FAILURE);
   }
   ```
   
   > This sets up a window with OpenGL context 4.1, configures multisampling, depth/stencil buffers, and ensures GLAD loads OpenGL functions. V-Sync is enabled for smooth rendering.

2. **Pipeline GPU**
   
   ```cpp
   // ======================= GPU Pipeline Setup =======================
   
   // Create a Vertex Array Object (VAO) to store vertex attribute configuration
   core::VAO vao{};
   
   // Create a Vertex Buffer Object (VBO) and upload vertex data to GPU
   core::VBO vbo{mesh::P_TRIANGLE_VERTICE, sizeof(mesh::P_TRIANGLE_VERTICE)};
   
   // Create an Element Buffer Object (EBO) and upload index data to GPU
   core::EBO ebo{mesh::P_TRIANGLE_INDICE, sizeof(mesh::P_TRIANGLE_INDICE)};
   
   // Compile and link shaders (vertex + fragment) into a GPU program
   core::Shader shader{(char *)mesh::P_TRIANGLE_VERT, (char *)mesh::P_TRIANGLE_FRAG};
   
   // Bind VAO to start recording configuration
   vao.bind();
   
   // Bind VBO: VAO will remember which VBO is used for vertex attributes
   vbo.bind();
   
   // Bind EBO: VAO will remember element indices for glDrawElements
   ebo.bind();
   
   // Configure vertex attribute pointer:
   // index = 0 (location in shader), size = 3 (x, y, z), type = GL_FLOAT,
   // stride = 3*sizeof(GLfloat), offset = 0
   vao.setAttributePointer(0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)(0));
   ```
   
   #### Pipeline Explanation:
   
   1. **VAO**: stores **vertex layout & bound buffers**
   
   2. **VBO**: stores **vertex positions on GPU**
   
   3. **EBO**: stores **indices to reuse vertices**
   
   4. **Attribute Config**: tells GPU **how to read vertex data**
   
   5. **Shader Program**: transforms vertices & colors fragments
   
   > Bind VAO => Bind VBO/EBO => Set attributes => Later draw using VAO => GPU knows exactly how to fetch vertices and indices.

3. Main loop rendering

4. cleanup

## Acknowledge

A big thanks to [LearnOpenGL](https://learnopengl.com) tutorials.