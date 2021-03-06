#include "RocketEngine/Core/OpenGLRenderer/Shader.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include <glad/glad.h>

#include "RocketEngine/Core/OpenGLRenderer/GLCall.h"

namespace RocketEngine
{
    Shader::Shader(const ShaderSources& shaderSources)
        : m_RendererID(0)
    {
        m_RendererID = CreateShader(shaderSources.VertexSource, shaderSources.FragmentSource);
    }

    Shader::~Shader()
    {
        GLCall(glDeleteProgram(m_RendererID));
    }

    unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
    {
        GLCall(unsigned int id = glCreateShader(type));
        const char* src = source.c_str();
        GLCall(glShaderSource(id, 1, &src, nullptr));
        GLCall(glCompileShader(id));

        int result;
        GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

        //Error Check
        if (result == GL_FALSE)
        {
            int lenght;
            GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght));
            char* message = (char*)alloca(lenght * sizeof(char));
            GLCall(glGetShaderInfoLog(id, lenght, &lenght, message));

            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
            std::cout << message << std::endl;

            GLCall(glDeleteShader(id));
            return 0;
        }
        return id;
    }

    unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLCall(unsigned int program = glCreateProgram());
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        GLCall(glAttachShader(program, vs));
        GLCall(glAttachShader(program, fs));
        GLCall(glLinkProgram(program));
        GLCall(glValidateProgram(program));

        GLCall(glDeleteShader(vs));
        GLCall(glDeleteShader(fs));

        return program;
    }


    void Shader::Bind() const
    {
        GLCall(glUseProgram(m_RendererID));
    }

    void Shader::Unbind() const
    {
        GLCall(glUseProgram(0));
    }

    void Shader::SetUniform1i(const std::string& name, int value)
    {
        GLCall(glUniform1i(GetUniformLocation(name), value));
    }

    void Shader::SetUniform1f(const std::string& name, float value)
    {
        GLCall(glUniform1f(GetUniformLocation(name), value));
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
    {
        GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
    }

    void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
    {
        GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
    {
        GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
    }

    int Shader::GetUniformLocation(const std::string& name)
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];
        
        GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
        if (location == -1)
            std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;
        
        m_UniformLocationCache[name] = location;
        return location;
    }
}