#pragma once

#include <vector>

#include "glm/glm.hpp"

namespace RocketEngine
{
    class Vertex
    {
    public:
        Vertex(int index, const glm::vec3& position)
            : m_Index(index), m_Position(position), m_Length(position.length())
        {
        }

        ~Vertex()
        {}

        const glm::vec3& GetPositon() const { return m_Position; }
        unsigned int GetIndex() const { return m_Index; }
        int GetTextureIndex() const { return m_TextureIndex; }
        int GetNormalIndex() const { return m_NormalIndex; }
        std::shared_ptr<Vertex> GetDuplicateVertex() const { return m_DuplicateVertex; }

        void SetTextureIndex(int textureIndex) { m_TextureIndex = textureIndex; }
        void SetNormalIndex(int normalIndex) { m_NormalIndex = normalIndex; }
        void SetDuplicateVertex(const Vertex& duplicateVertex) { m_DuplicateVertex = std::make_shared<Vertex>(duplicateVertex); }

        bool isSet() const { return m_TextureIndex != -1 && m_NormalIndex != -1; }
        bool hasSameTextureAndNormal(int otherTextureIndex, int otherNormalIndex) const { return m_TextureIndex == otherTextureIndex && m_NormalIndex == otherNormalIndex; }


        void avarageTangents()
        {
            if (m_Tangents.empty())
                return;
            for (glm::vec3 tangent : m_Tangents)
            {
                m_AveragedTangent = m_AveragedTangent + tangent;
            }
            glm::normalize(m_AveragedTangent);
        }


    private:
        glm::vec3 m_Position;
        int m_TextureIndex = -1;
        int m_NormalIndex = -1;

        std::shared_ptr<Vertex> m_DuplicateVertex = nullptr;

        unsigned int m_Index;
        float m_Length;
        
        std::vector<glm::vec3> m_Tangents;
        glm::vec3 m_AveragedTangent = { 0.0f, 0.0f, 0.0f };
    };
}