#include "RocketEngine/Components/Material.h"

namespace RocketEngine
{
    Material::Material(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& texture)
        :m_Shader(shader), m_Texture(texture)
    {
        shinyDamper = 10;
        reflectivity = 1;
    }

    Material::~Material()
    {}
}