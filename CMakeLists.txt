cmake_minimum_required(VERSION 3.10)
project(learnopengl)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CPP_SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/**/*.cpp")

# GLAD (add C file)
list(APPEND CPP_SOURCES lib/glad/src/glad.c)

# find shader files
file(GLOB_RECURSE SHADERS CONFIGURE_DEPENDS
  "res/**/*.frag"
  "res/**/*.vert"
  "res/**/*.glsl"
)
list(REMOVE_DUPLICATES SHADERS)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)

set(SHADER_C_FILES)
foreach(SHADER ${SHADERS})
  message(${SHADER})

  get_filename_component(NAME_WE ${SHADER} NAME_WE)
  get_filename_component(EXT ${SHADER} EXT)
  string(REPLACE "." "_" EXT_SAFE ${EXT})
  set(OUTPUT_C ${CMAKE_BINARY_DIR}/shaders/${NAME_WE}${EXT_SAFE}.c)

  add_custom_command(
    OUTPUT ${OUTPUT_C}
    COMMAND python3 
            ${CMAKE_SOURCE_DIR}/glsl2c.py 
            ${SHADER} 
            ${OUTPUT_C}
    DEPENDS ${SHADER} 
            ${CMAKE_SOURCE_DIR}/glsl2c.py
    COMMENT "Converting shader ${NAME_WE}${EXT} to C file"
    VERBATIM
  )

  list(APPEND SHADER_C_FILES ${OUTPUT_C})
endforeach()

add_custom_target(Shaders ALL DEPENDS ${SHADER_C_FILES})

add_executable(main ${CPP_SOURCES} ${SHADER_C_FILES})
add_definitions(-g)

add_dependencies(main Shaders)

target_include_directories(main PRIVATE
  inc # project
  res/render # ressources (primitive)
  lib/glad/include # glad
  lib/glfw/include # glfw
  lib/glm # glm
  lib/imgui # imgui
  lib/stb # stb
)

# GLFW (remove all flags)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

target_link_libraries(main PRIVATE glfw)

# search for OpenGL libs
find_package(OpenGL REQUIRED)
target_link_libraries(main PRIVATE OpenGL::GL)

# find OpenGL dependancies
if(APPLE) # MacOS
  target_link_libraries(main PRIVATE
    "-framework Cocoa" "-framework IOKit" "-framework CoreVideo"
  )
elseif(WIN32) # Windows
  target_link_libraries(main PRIVATE
    opengl32 gdi32 user32 shell32
  )
elseif(UNIX) # Most UNIX computer
  target_link_libraries(main PRIVATE
    X11 pthread dl m
  )
endif()
