#include "RocketEngine/Core/Input/Input.h"

#include <GLFW/glfw3.h>

namespace RocketEngine
{
    bool Input::KeyPressedImpl(int keycode)
    {
        GLFWwindow* window = glfwGetCurrentContext();
        int state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::MouseButtonPressedImpl(int button)
    {
        GLFWwindow* window = glfwGetCurrentContext();
        int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::MousePositionImpl()
    {
        GLFWwindow* window = glfwGetCurrentContext();
        double  xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return glm::vec2(xpos, ypos);
    }
}