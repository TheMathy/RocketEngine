#pragma once

#include "glm/glm.hpp"

namespace RocketEngine
{
    class Transform
    {
    public:
        Transform(const glm::vec3& initPosition = { 0.0f, 0.0f, 0.0f }, const glm::vec3& initRotation = { 0.0f, 0.0f, 0.0f }, const glm::vec3& initScale = { 0.0f, 0.0f, 0.0f }, bool inversed = false);
        ~Transform();
    public:
        glm::vec3 position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 scale = { 1.0f, 1.0f, 1.0f };
    public:
        const glm::mat4& GetModelMatrix() { RecalculateModalMatrix(); return m_ModelMatrix; }
    private:
        glm::mat4 m_ModelMatrix;
        bool m_Inversed;
    private:
        void RecalculateModalMatrix();
    };
}