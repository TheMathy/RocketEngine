#include "RocketEngine/Terrain/Terrain.h"

namespace RocketEngine
{
    Terrain::Terrain(const Transform& transform, const std::shared_ptr<Material>& material, float size, uint32_t vertexCount)
        : GameObject(transform, nullptr, material), m_Size(size), m_VertexCount(vertexCount)
    {
        GameObject::SetMesh(GenerateTerrain());
    }
    
    Terrain::~Terrain()
    {}

    std::shared_ptr<Mesh> Terrain::GenerateTerrain()
    {
        uint32_t count = m_VertexCount * m_VertexCount;

        float vertices[count * 8];

        unsigned int indices[6 * (m_VertexCount - 1) * (m_VertexCount - 1)];

        // Load positions, textureCoords and normals
        uint32_t vertexPointer = 0;

        for (uint32_t i = 0; i < m_VertexCount; i++)
        {
            for (uint32_t j = 0; j < m_VertexCount; j++)
            {
                vertices[vertexPointer * 8] = (float)j / ((float)m_VertexCount - 1) * m_Size;
                vertices[vertexPointer * 8 + 1] = 0;
                vertices[vertexPointer * 8 + 2] = (float)i / ((float)m_VertexCount - 1) * m_Size;

                vertices[vertexPointer * 8 + 3] = (float)j / ((float)m_VertexCount - 1);
                vertices[vertexPointer * 8 + 4] = (float)i / ((float)m_VertexCount - 1);

                vertices[vertexPointer * 8 + 5] = 0;
                vertices[vertexPointer * 8 + 6] = 1;
                vertices[vertexPointer * 8 + 7] = 0;

                vertexPointer ++;
            }
        }

        // Load indices
        int pointer = 0;

        for (uint32_t gz = 0; gz < m_VertexCount - 1; gz++)
        {
            for (uint32_t gx = 0; gx < m_VertexCount - 1; gx++)
            {
                unsigned int topLeft = (gz * m_VertexCount) + gx;
                unsigned int topRight = topLeft + 1;
                unsigned int bottomLeft = ((gz + 1) * m_VertexCount) + gx;
                unsigned int bottomRight = bottomLeft + 1;

                indices[pointer++] = topLeft;
                indices[pointer++] = bottomLeft;
                indices[pointer++] = topRight;

                indices[pointer++] = topRight;
                indices[pointer++] = bottomLeft;
                indices[pointer++] = bottomRight;
            }
        }

        std::shared_ptr<Mesh> mesh(new Mesh(vertices, count * 8 * sizeof(float), indices, 6 * (m_VertexCount - 1) * (m_VertexCount - 1)));
        return mesh;
    }

}