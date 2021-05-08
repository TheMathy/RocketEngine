#include "RocketEngine/Core/Objects/LightSource.h"

namespace RocketEngine
{
    LightSource::LightSource(const Transform& transform, const glm::vec3& color)
        : m_Color(color), GameObject(transform, nullptr, nullptr)
    {}

    LightSource::~LightSource()
    {}
}