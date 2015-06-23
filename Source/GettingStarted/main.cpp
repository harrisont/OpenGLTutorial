// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

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

// Return nullptr on compile success, error-string on failure.
std::unique_ptr<std::string> CompileShader(GLuint shaderId)
{
    glCompileShader(shaderId);
    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderId, sizeof(infoLog), nullptr /*length*/, infoLog);
        return std::make_unique<std::string>(infoLog);
    }
    return nullptr;
}

// Return nullptr on compile success, error-string on failure.
std::unique_ptr<std::string> LinkShaderProgram(GLuint programId)
{
    glLinkProgram(programId);
    GLint success;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[1024];
        glGetProgramInfoLog(programId, sizeof(infoLog), nullptr /*length*/, infoLog);
        return std::make_unique<std::string>(infoLog);
    }
    return nullptr;
}

void Render(const GLuint shaderProgramId, const GLuint vertexArrayId)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgramId);
    glBindVertexArray(vertexArrayId);
    glDrawArrays(GL_TRIANGLES, 0 /*first*/, 3 /*count*/);
    glBindVertexArray(0);
}

enum class MainLoopResult
{
    error,
    success,
};

MainLoopResult MainLoop(GLFWwindow* const window)
{
    const GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* const vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}\0";
    glShaderSource(vertexShaderId, 1 /*count*/, &vertexShaderSource, nullptr /*length*/);
    const auto compileVertexShaderError = CompileShader(vertexShaderId);
    if (compileVertexShaderError)
    {
        std::cerr << "Failed to compile vertex shader. " << *compileVertexShaderError << std::endl;
        return MainLoopResult::error;
    }

    const GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* const fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
        "}\0";
    glShaderSource(fragmentShaderId, 1 /*count*/, &fragmentShaderSource, nullptr /*length*/);
    const auto compileFragmentShaderError = CompileShader(fragmentShaderId);
    if (compileFragmentShaderError)
    {
        std::cerr << "Failed to fragment vertex shader. " << *compileFragmentShaderError << std::endl;
        return MainLoopResult::error;
    }

    const GLuint shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    const auto linkShaderProgramError = LinkShaderProgram(shaderProgramId);
    if (linkShaderProgramError)
    {
        std::cerr << "Failed to link shader program. " << *linkShaderProgramError << std::endl;
        return MainLoopResult::error;
    }
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    GLuint vertexArrayId;
    glGenVertexArrays(1 /*n*/, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    GLuint vertexBufferId;
    {
        glGenBuffers(1 /*n*/, &vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
             0.5f, -0.5f, 0.0f, // right
             0.0f,  0.5f, 0.0f  // top
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0 /*index*/, 3 /*size*/, GL_FLOAT /*type*/, GL_FALSE /*normalized*/, 3 * sizeof(GLfloat) /*stride*/, nullptr /*pointer*/);
        glEnableVertexAttribArray(0 /*index*/);
    }
    glBindVertexArray(0 /*array*/);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        Render(shaderProgramId, vertexArrayId);
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1 /*n*/, &vertexArrayId);
    glDeleteBuffers(1 /*n*/, &vertexBufferId);

    return MainLoopResult::success;
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

    const auto mainLoopResult = MainLoop(window);
    if (mainLoopResult == MainLoopResult::error)
    {
        return false;
    }

    glfwTerminate();
    return true;
}

int main()
{
    return Run() ? 0 : 1;
}