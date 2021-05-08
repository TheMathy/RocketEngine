#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "RocketEngine/Core/OpenGLRenderer/Renderer.h"
#include "RocketEngine/Core/Objects/GameObject.h"
#include "RocketEngine/Core/Objects/Camera.h"
#include "RocketEngine/Core/Objects/LightSource.h"

namespace RocketEngine
{
    class MasterRenderer : public Renderer
    {
    public:
        MasterRenderer();
        ~MasterRenderer();
    public:
        void Prepare() override;
        void Submit(GameObject& gameObject);
        //void RenderObject(Object& object, Camera& camera, LightSource& lightSource);
        void RenderScene(Camera& camera, LightSource& lightSource);
        std::unordered_map<std::shared_ptr<Material>, std::vector<GameObject*>> m_ObjectMaterialBatch;
    };
}