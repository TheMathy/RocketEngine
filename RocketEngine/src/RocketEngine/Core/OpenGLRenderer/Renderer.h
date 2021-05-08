#pragma once

#include "glm/glm.hpp"

#include "RocketEngine/Core/OpenGLRenderer/VertexArray.h"
#include "RocketEngine/Core/OpenGLRenderer/IndexBuffer.h"
#include "RocketEngine/Core/OpenGLRenderer/Shader.h"
#include "RocketEngine/Core/OpenGLRenderer/Texture.h"

namespace RocketEngine
{
    class Renderer
    {
    public:
        Renderer();
        virtual ~Renderer();
    public:
        virtual void Prepare();

        void BasicRender(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture, const glm::vec4& color);
        void Clear(const glm::vec4& color);
    };
}