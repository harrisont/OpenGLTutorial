#include "Shader.h"
#include <Core/File.h>
#include <iostream>
#include <string>

namespace
{
    // Return nullptr on compile success, error-string on failure.
    optional<std::string> CompileShader(ShaderId shaderId)
    {
        glCompileShader(shaderId);
        GLint success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderId, sizeof(infoLog), nullptr /*length*/, infoLog);
            return MakeOptional<std::string>(infoLog);
        }
        return nullptr;
    }

    enum class ShaderType
    {
        vertex = GL_VERTEX_SHADER,
        fragment = GL_FRAGMENT_SHADER,
    };

    optional<ShaderId> CreateShader(const ShaderType type, const char* const filePath)
    {
        const auto id = glCreateShader(static_cast<GLenum>(type));
        const auto source = FileRead(filePath);
        const auto sourceCstr = source.c_str();
        glShaderSource(id, 1 /*count*/, &sourceCstr, nullptr /*length*/);

        const auto compileError = CompileShader(id);
        if (compileError)
        {
            std::cerr << "Failed to compile shader \"" << filePath << "\". " << *compileError << std::endl;
            return nullptr;
        }

        return MakeOptional<ShaderId>(id);
    }

    // Return nullptr on compile success, error-string on failure.
    optional<std::string> LinkShaderProgram(GLuint programId)
    {
        glLinkProgram(programId);
        GLint success;
        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetProgramInfoLog(programId, sizeof(infoLog), nullptr /*length*/, infoLog);
            return MakeOptional<std::string>(infoLog);
        }
        return nullptr;
    }
}

optional<VertexShader> CreateVertexShader(const char* const filePath)
{
    const auto maybeId = CreateShader(ShaderType::vertex, filePath);
    return maybeId ? MakeOptional<VertexShader>(*maybeId) : nullptr;
}

optional<FragmentShader> CreateFragmentShader(const char* const filePath)
{
    const auto maybeId = CreateShader(ShaderType::fragment, filePath);
    return maybeId ? MakeOptional<FragmentShader>(*maybeId) : nullptr;
}

optional<ShaderProgram> CreateShaderProgram(VertexShader&& vertexShader, FragmentShader&& fragmentShader)
{
    const auto programId = glCreateProgram();

    glAttachShader(programId, vertexShader.id);
    glAttachShader(programId, fragmentShader.id);

    const auto linkError = LinkShaderProgram(programId);
    if (linkError)
    {
        std::cerr << "Failed to link shader program. " << *linkError << std::endl;
        return nullptr;
    }

    glDeleteShader(vertexShader.id);
    glDeleteShader(fragmentShader.id);

    return MakeOptional<ShaderProgram>(programId);
}
