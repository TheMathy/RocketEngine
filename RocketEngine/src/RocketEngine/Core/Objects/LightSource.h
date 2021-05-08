#pragma once

#include "RocketEngine/Core/Objects/GameObject.h"

namespace RocketEngine
{
    class LightSource : public GameObject
    {
    public:
        LightSource(const Transform& transform, const glm::vec3& color);
        ~LightSource();
    public:
        const glm::vec3& GetColor() const { return m_Color; }
    private:
        glm::vec3 m_Color;
    };
}