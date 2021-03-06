#pragma once

#include "RocketEngine/Core/OpenGLRenderer/VertexBuffer.h"
#include "RocketEngine/Core/OpenGLRenderer/VertexArray.h"
#include "RocketEngine/Core/OpenGLRenderer/IndexBuffer.h"

namespace RocketEngine
{
    class Mesh
    {
    public:
        Mesh(const void* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesCount);
        ~Mesh();
    public:
        const VertexArray& GetVertexArray() const { return m_VertexArray; }
        const IndexBuffer& GetIndexBuffer() const { return m_IndexBuffer; }
    private:
        VertexBuffer m_VertexBuffer;
        VertexArray m_VertexArray;
        IndexBuffer m_IndexBuffer;
    };
}