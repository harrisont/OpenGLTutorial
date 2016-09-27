#include "Shader.h"
#include <Core/Macros.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <SOIL.h>

#include <algorithm>
#include <assert.h>
#include <iostream>
#include <memory>
#include <string>

float gMixValue = 0.5f;

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
    else if (key == GLFW_KEY_UP)
    {
        gMixValue = std::min(1.0f, gMixValue + 0.05f);
    }
    else if (key == GLFW_KEY_DOWN)
    {
        gMixValue = std::max(0.0f, gMixValue - 0.05f);
    }
}

using TextureId = GLuint;

struct Texture
{
    const TextureId id;

    Texture(TextureId id)
        : id(id)
    {
    }

    Texture& operator=(const Texture&) = delete;
};

void Render(
    const ShaderProgram& shaderProgram,
    const GLuint vertexArrayId,
    const unsigned vertexCount,
    const Texture texture1,
    const Texture texture2,
    const float mixValue)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram.id);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1.id);
    glUniform1i(glGetUniformLocation(shaderProgram.id, "ourTexture1"), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2.id);
    glUniform1i(glGetUniformLocation(shaderProgram.id, "ourTexture2"), 1);

    glUniform1f(glGetUniformLocation(shaderProgram.id, "mixValue"), mixValue);

    glBindVertexArray(vertexArrayId);
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT /*type*/, 0 /*indices*/);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture LoadAndBindTexture(const char* const imagePath)
{
    int width, height;
    unsigned char* imageData = SOIL_load_image(imagePath, &width, &height, nullptr /*channels*/, SOIL_LOAD_RGB);
    if (!imageData)
    {
        std::cerr << "Failed to load image \"" << imagePath << "\": " << SOIL_last_result() << std::endl;
    }
    TextureId id;
    glGenTextures(1 /*n*/, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0 /*level*/, GL_RGB, width, height, 0 /*border*/, GL_RGB, GL_UNSIGNED_BYTE, imageData);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(imageData);
    glBindTexture(GL_TEXTURE_2D, 0);
    return Texture(id);
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
    unsigned int vertexCount = 0;
    {
        glGenBuffers(1 /*n*/, &vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        GLfloat vertices[] = {
            // Positions          // Colors           // Texture Coords
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // Top Right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Bottom Right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top Left
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glGenBuffers(1 /*n*/, &elementBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
        GLuint indices[] = {
            0, 1, 2,  // 1st triangle
            2, 3, 0,  // 2nd triangle
        };
        vertexCount = ARRAY_LENGTH(indices);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0 /*index*/, 3 /*size*/, GL_FLOAT /*type*/, GL_FALSE /*normalized*/, 8 * sizeof(GLfloat) /*stride*/, nullptr /*pointer*/);
        glEnableVertexAttribArray(0 /*index*/);
        glVertexAttribPointer(1 /*index*/, 3 /*size*/, GL_FLOAT /*type*/, GL_FALSE /*normalized*/, 8 * sizeof(GLfloat) /*stride*/, reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)) /*pointer*/);
        glEnableVertexAttribArray(1 /*index*/);
        glVertexAttribPointer(2 /*index*/, 2 /*size*/, GL_FLOAT /*type*/, GL_FALSE /*normalized*/, 8 * sizeof(GLfloat) /*stride*/, reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)) /*pointer*/);
        glEnableVertexAttribArray(2 /*index*/);
    }
    glBindVertexArray(0 /*array*/);

    Texture texture1 = LoadAndBindTexture("container.jpg");
    Texture texture2 = LoadAndBindTexture("awesomeface.png");

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        Render(shaderProgram, vertexArrayId, vertexCount, texture1, texture2, gMixValue);
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

void PrintUsage()
{
    std::cout << "Usage:" << std::endl
        << "\tEsc: quit" << std::endl
        << "\tUp/Down: texture blending" << std::endl;
}

int main()
{
    PrintUsage();

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
