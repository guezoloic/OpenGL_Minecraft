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

## Acknowledge
A big thanks to [LearnOpenGL](https://learnopengl.com) tutorials.