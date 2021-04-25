#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "RocketEngine/Objects/GameObject.h"
#include "RocketEngine/Window/Window.h"

namespace RocketEngine
{
    class Camera : public GameObject
    {
    public:
        Camera(Window& window, const glm::vec4& backgroundColor, float fieldOfView, float nearPlane, float farPlane);
        ~Camera();
    public:
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() { return GameObject::transform.GetModelMatrix(); }
    private:
        Window& m_Window;
    public:
        glm::vec4 backgroundColor;
    private:
        float m_FieldOfView;
        float m_NearPlane;
        float m_FarPlane;
    private:
        glm::mat4 m_ProjectionMatrix;
    };
}



/*
class Camera
{
public:
    Camera(const Window& window, float fieldOfView, float nearPlane, float farPlane);
    ~Camera();

    void Move();

    const glm::vec3& GetPosition() const { return m_Position; }
    void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

    float GetPitch() const { return m_Pitch; }
    void SetPitch(float pitch) { m_Pitch = pitch; RecalculateViewMatrix(); }

    inline float GetYaw() const { return m_Yaw; }
    void SetYaw(float yaw) { m_Pitch = yaw; RecalculateViewMatrix(); }

    inline float GetRoll() const { return m_Roll; }
    void SetRoll(float roll) { m_Roll = roll; RecalculateViewMatrix(); }

    const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
    const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
private:
    void RecalculateViewMatrix();
private:
    float m_FieldOfView;
    float m_NearPlane;
    float m_FarPlane;

    Window m_Window;

    glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
    float m_Pitch = 0.0f;
    float m_Yaw = 0.0f;
    float m_Roll = 0.0f;

    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
};
*/