#include "RocketEngine/Core/Objects/GameObject.h"

namespace RocketEngine
{
    GameObject::GameObject(const Transform& transform, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material)
        :transform(transform), m_Mesh(mesh), m_Material(material)
    {}

    GameObject::~GameObject()
    {}
}
