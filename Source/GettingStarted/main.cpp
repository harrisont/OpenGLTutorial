#include "Shader.h"

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <SOIL.h>

#include <assert.h>
#include <iostream>
#include <memory>
#include <string>

bool InitGlfw()
{
    if (glfwInit() == GL_FALSE)
    {
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    return true;
}

GLFWwindow* CreateWindow(const int width, const int height)
{
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    const char* const title = "LearnOpenGL";
    GLFWwindow* const window = glfwCreateWindow(width, height, title, nullptr /*monitor*/, nullptr /*share*/);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    return window;
}

bool InitGlew()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return false;
    }
    return true;
}

void KeyCallback(GLFWwindow* const window, const int key, const int /*scancode*/, const int action, const int /*mods*/)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void Render(const ShaderProgram& shaderProgram, const GLuint vertexArrayId)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram.id);

    glBindVertexArray(vertexArrayId);
    glDrawElements(GL_TRIANGLES, 6 /*count*/, GL_UNSIGNED_INT /*type*/, 0 /*indices*/);
    glBindVertexArray(0);
}

void MainLoop(GLFWwindow* const window)
{
    const auto maybeVertexShader = CreateVertexShader("shader.vert");
    assert(maybeVertexShader);
    const auto maybeFragmentShader = CreateFragmentShader("shader.frag");
    assert(maybeFragmentShader);
    const auto maybeShaderProgram = CreateShaderProgram(std::move(*maybeVertexShader), std::move(*maybeFragmentShader));
    assert(maybeShaderProgram);
    const auto shaderProgram = *maybeShaderProgram;

    GLuint vertexArrayId;
    glGenVertexArrays(1 /*n*/, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    GLuint vertexBufferId;
    GLuint elementBufferId;
    {
        glGenBuffers(1 /*n*/, &vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        GLfloat vertices[] = {
            // Positions         // Colors
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // Bottom Right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // Bottom Left
             0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // Top
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1 /*n*/, &elementBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
        GLuint indices[] = {
            0, 1, 2,  // 1st triangle
        };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0 /*index*/, 3 /*size*/, GL_FLOAT /*type*/, GL_FALSE /*normalized*/, 6 * sizeof(GLfloat) /*stride*/, nullptr /*pointer*/);
        glEnableVertexAttribArray(0 /*index*/);
        glVertexAttribPointer(1 /*index*/, 3 /*size*/, GL_FLOAT /*type*/, GL_FALSE /*normalized*/, 6 * sizeof(GLfloat) /*stride*/, reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) /*pointer*/);
        glEnableVertexAttribArray(1 /*index*/);
    }
    glBindVertexArray(0 /*array*/);

    int width, height;
    unsigned char* image = SOIL_load_image("container.jpg", &width, &height, nullptr /*channels*/, SOIL_LOAD_RGB);
    (void)image;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        Render(shaderProgram, vertexArrayId);
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1 /*n*/, &vertexArrayId);
    glDeleteBuffers(1 /*n*/, &vertexBufferId);
}

// Return true on success, false on failure.
bool Run()
{
    if (!InitGlfw())
    {
        return false;
    }

    const int width = 800;
    const int height = 600;
    GLFWwindow* const window = CreateWindow(width, height);
    if (!window)
    {
        return false;
    }

    glfwSetKeyCallback(window, KeyCallback);

    if (!InitGlew())
    {
        return false;
    }

    glViewport(0 /*x*/, 0 /*y*/, width, height);

    MainLoop(window);
    glfwTerminate();
    return true;
}

int main()
{
    try
    {
        return Run() ? 0 : 1;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}