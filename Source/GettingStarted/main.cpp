// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

#include <iostream>

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
        std::cout << "Failed to create GLFW window" << std::endl;
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
        std::cout << "Failed to initialize GLEW" << std::endl;
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

bool Run()
{
    if (!InitGlfw())
    {
        return 1;
    }

    const int width = 800;
    const int height = 600;
    GLFWwindow* const window = CreateWindow(width, height);
    if (!window)
    {
        return 1;
    }

    glfwSetKeyCallback(window, KeyCallback);

    if (!InitGlew())
    {
        return 1;
    }

    glViewport(0 /*x*/, 0 /*y*/, width, height);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

int main()
{
    return Run() ? 0 : 1;
}