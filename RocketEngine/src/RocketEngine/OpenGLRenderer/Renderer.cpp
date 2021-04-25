#include "RocketEngine/OpenGLRenderer/Renderer.h"

#include <iostream>

#include <glad/glad.h>

#include "RocketEngine/OpenGLRenderer/GLCall.h"

namespace RocketEngine
{
    Renderer::Renderer()
    {}

    Renderer::~Renderer()
    {}

    void Renderer::Prepare()
    {
        GLCall(glEnable(GL_DEPTH_TEST));
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    }

    void Renderer::BasicRender(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shader& shader, const Texture& texture, const glm::vec4& color)
    {
        Clear(color);
        
        vertexArray.Bind();
        indexBuffer.Bind();
        texture.Bind();
        shader.Bind();

        GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr));

        vertexArray.Unbind();
        indexBuffer.Unbind();
        texture.Unbind();
        shader.Unbind();
    }

    void Renderer::Clear(const glm::vec4& color)
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
        GLCall(glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f));
    }
}