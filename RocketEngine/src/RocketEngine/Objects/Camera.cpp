#include "RocketEngine/Objects/Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RocketEngine
{
    Camera::Camera(Window& window, const glm::vec4& backgroundColor, float fieldOfView, float nearPlane, float farPlane)
        : m_Window(window), backgroundColor(backgroundColor), m_FieldOfView(fieldOfView), m_NearPlane(nearPlane), m_FarPlane(farPlane),
        m_ProjectionMatrix(glm::perspective(fieldOfView, (float)window.GetWidth() / (float)window.GetHeight(), nearPlane, farPlane)), 
        GameObject(Transform(glm::vec3(0.0f, 0.0f, -0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), true), nullptr, nullptr)
    {}

    Camera::~Camera()
    {}
}

/*
void Camera::Move()
{
    GLFWwindow* window = static_cast<GLFWwindow*>(m_Window.GetNativeWindow());
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_REPEAT)
    {
        m_Position.z -= 0.02f;
        RecalculateViewMatrix();
    }
        
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_REPEAT)
    {
        m_Position.x += 0.02f;
        RecalculateViewMatrix();
    }
        
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_REPEAT)
    {
        m_Position.x -= 0.02f;
        RecalculateViewMatrix();
    }
}
*/