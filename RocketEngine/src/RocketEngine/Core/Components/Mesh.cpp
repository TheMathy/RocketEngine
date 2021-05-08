#include "RocketEngine/Core/Components/Mesh.h"

#include "RocketEngine/Core/OpenGLRenderer/VertexBufferLayout.h"

namespace RocketEngine
{
    Mesh::Mesh(const void* vertices, unsigned int verticesSize, const unsigned int* indices, unsigned int indicesCount)
        :m_VertexBuffer(vertices, verticesSize), m_IndexBuffer(indices, indicesCount), m_VertexArray()
    {
        m_VertexArray.Bind();
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        layout.Push<float>(3);

        m_VertexArray.AddBuffer(m_VertexBuffer, layout);

        m_VertexArray.Unbind();
    }

    Mesh::~Mesh()
    {}
}