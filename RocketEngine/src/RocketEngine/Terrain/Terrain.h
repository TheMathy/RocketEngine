#pragma once

#include "RocketEngine/Core/Objects/GameObject.h"

namespace RocketEngine
{
    class Terrain : public GameObject
    {
    public:
        Terrain(const Transform& transform, const std::shared_ptr<Material>& material, float size, uint32_t vertexCount);
        ~Terrain();
    private:
        std::shared_ptr<Mesh> GenerateTerrain();
    private:
        float m_Size;
        uint32_t m_VertexCount;
    };
}