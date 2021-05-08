#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

namespace RocketEngine
{
    struct ShaderSources
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class Shader
    {
    public:
        Shader(const ShaderSources& shaderSources);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        //Set uniforms
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform3f(const std::string& name, float v0, float v1, float v2);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
        
    private:
        unsigned int m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;

    private:
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

        int GetUniformLocation(const std::string& name);
    };
}