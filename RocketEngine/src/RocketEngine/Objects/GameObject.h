#pragma once

#include <memory>

#include "RocketEngine/Components/Transform.h"
#include "RocketEngine/Components/Mesh.h"
#include "RocketEngine/Components/Material.h"

namespace RocketEngine
{
    class GameObject
    {
    public:
        GameObject(const Transform& transform, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material);
        virtual ~GameObject();

        const std::shared_ptr<Mesh>& GetMesh() const { return m_Mesh; }
        const std::shared_ptr<Material>& GetMaterial() const { return m_Material; }

        void SetMesh(const std::shared_ptr<Mesh>& mesh) { m_Mesh = mesh; }
        void SetMaterial(const std::shared_ptr<Material>& material) { m_Material.reset(); m_Material = material; }
    public:
        Transform transform;
    private:
        std::shared_ptr<Mesh> m_Mesh;
        std::shared_ptr<Material> m_Material;
    };
}