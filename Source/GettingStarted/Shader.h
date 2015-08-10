#pragma once

#include <Core/Optional.h>

#include <GL/glew.h>

using ShaderId = const GLuint;

struct VertexShader
{
    const ShaderId id;

    VertexShader(ShaderId id)
        : id(id)
    {
    }

    VertexShader& operator=(const VertexShader&) = delete;
};

struct FragmentShader
{
    const ShaderId id;

    FragmentShader(ShaderId id)
        : id(id)
    {
    }

    FragmentShader& operator=(const FragmentShader&) = delete;
};

optional<VertexShader> CreateVertexShader(const char* const filePath);
optional<FragmentShader> CreateFragmentShader(const char* const filePath);


struct ShaderProgram
{
    const ShaderId id;

    ShaderProgram(ShaderId id)
        : id(id)
    {
    }

    ShaderProgram& operator=(const ShaderProgram&) = delete;
};

optional<ShaderProgram> CreateShaderProgram(VertexShader&& vertexShader, FragmentShader&& fragmentShader);
