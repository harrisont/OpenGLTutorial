cmake_minimum_required(VERSION 3.3)
project(OpenGLTutorial)

# CMAKE_SOURCE_DIR should be at /[root]/Source/.
get_filename_component(repositoryDir ${CMAKE_SOURCE_DIR}/.. ABSOLUTE)

set(sourceDir ${repositoryDir}/Source)
set(buildDir ${repositoryDir}/Build)
set(cmakeScriptsDir ${sourceDir}/CMakeScripts)

include_directories(
    ${sourceDir})

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include("${cmakeScriptsDir}/BuildFlags.cmake")

add_subdirectory(External)
add_subdirectory(Core)
add_subdirectory(GettingStarted)
