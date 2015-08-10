include("${cmakeScriptsDir}/AddGlobbedFiles.cmake")

project(GettingStarted)

set(EXECUTABLE_OUTPUT_PATH ${buildDir}/${PROJECT_NAME})

AddGlobbedFiles(source .)

include_directories(
    ${sourceDir}/External/glfw-3.1.1.bin.WIN32/include
    ${sourceDir}/External/glew-1.12.0/include
    "${sourceDir}/External/Simple OpenGL Image Library/src")

add_executable(${PROJECT_NAME} ${sourceFiles})

target_link_libraries(${PROJECT_NAME}
    Core

    # External
    glfw
    glew_s
    SOIL)

#${CMAKE_CURRENT_SOURCE_DIR}
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/RuntimeResources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)
