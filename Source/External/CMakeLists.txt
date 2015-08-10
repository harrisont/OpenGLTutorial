set(BUILD_UTILS OFF CACHE BOOL "Build GLEW utilities")
add_subdirectory(glew-1.12.0/build/cmake)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")
add_subdirectory(glfw-3.1.1)

add_subdirectory("Simple OpenGL Image Library")
