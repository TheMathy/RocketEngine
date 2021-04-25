#pragma once

#include "glm/glm.hpp"

#include "RocketEngine/OpenGLRenderer/VertexArray.h"
#include "RocketEngine/OpenGLRenderer/IndexBuffer.h"
#include "RocketEngine/OpenGLRenderer/Shader.h"
#include "RocketEngine/OpenGLRenderer/Texture.h"

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