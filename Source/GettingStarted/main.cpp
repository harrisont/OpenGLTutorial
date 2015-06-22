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

bool InitWindow()
{
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    const int width = 800;
    const int height = 600;
    const char* const title = "LearnOpenGL";
    GLFWwindow* const window = glfwCreateWindow(width, height, title, nullptr /*monitor*/, nullptr /*share*/);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(window);
    glViewport(0 /*x*/, 0 /*y*/, width, height);
    return true;
}

int main()
{
    if (!InitGlfw())
    {
        return 1;
    }

    if (!InitGlew())
    {
        return 1;
    }

    if (!InitWindow())
    {
        return 1;
    }

    glfwTerminate();

    return 0;
}