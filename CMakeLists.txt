cmake_minimum_required(VERSION 3.10)
project(learnopengl)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE CPP_HEADERS CONFIGURE_DEPENDS src/*.hpp)

list(APPEND CPP_SOURCES lib/glad/src/glad.c)
add_executable(main ${CPP_SOURCES} ${CPP_HEADERS})

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

# GLAD
target_include_directories(main PRIVATE lib/glad/include)

# GLM
target_include_directories(main PRIVATE lib/glm)

# STB
target_include_directories(main PRIVATE lib/stb)

target_include_directories(main PRIVATE inc/)

target_link_libraries(main PRIVATE glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(main PRIVATE OpenGL::GL)

if(APPLE)
    target_link_libraries(main PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
elseif(WIN32)
    target_link_libraries(main PRIVATE
        opengl32
        gdi32
        user32
        shell32
    )
elseif(UNIX)
    target_link_libraries(main PRIVATE
        X11
        pthread
        dl
        m
    )
endif()