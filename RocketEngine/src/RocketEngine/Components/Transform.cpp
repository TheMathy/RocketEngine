#include "RocketEngine/Components/Transform.h"

#include <glm/gtc/matrix_transform.hpp>

namespace RocketEngine
{
    Transform::Transform(const glm::vec3& initPosition, const glm::vec3& initRotation, const glm::vec3& initScale, bool inversed)
        : position(initPosition), rotation(initRotation), scale(initScale), m_Inversed(inversed)
    {
        RecalculateModalMatrix();
    }

    Transform::~Transform()
    {}

    void Transform::RecalculateModalMatrix()
    {
        glm::mat4 newModelMatrix(1.0f);
        
        newModelMatrix = glm::translate(newModelMatrix, position);

        newModelMatrix = glm::rotate(newModelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        newModelMatrix = glm::rotate(newModelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        newModelMatrix = glm::rotate(newModelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

        newModelMatrix = glm::scale(newModelMatrix, scale);

        if (m_Inversed)
            m_ModelMatrix = glm::inverse(newModelMatrix);
        else
            m_ModelMatrix = newModelMatrix;
    }
}