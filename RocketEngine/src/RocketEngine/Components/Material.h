#pragma once

#include <memory>

#include "RocketEngine/OpenGLRenderer/Shader.h"
#include "RocketEngine/OpenGLRenderer/Texture.h"

namespace RocketEngine
{
    class Material
    {
    public:
        Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture);
        ~Material();
    public:
        float shinyDamper;
        float reflectivity;
    public:
        const std::shared_ptr<Shader>& GetShader() const { return m_Shader; }
        const std::shared_ptr<Texture>& GetTexture() const { return m_Texture; }
    private:
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<Texture> m_Texture;
    };
}