include("${cmakeScriptsDir}/AddGlobbedFiles.cmake")

project(SOIL)

AddGlobbedFiles(source src)
list(REMOVE_ITEM sourceFiles "${CMAKE_CURRENT_SOURCE_DIR}/src/test_SOIL.cpp")

include_directories(
    src)

add_library(${PROJECT_NAME} STATIC ${sourceFiles})
