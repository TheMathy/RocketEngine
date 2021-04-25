#include "RocketEngine/Window/Window.h"

#include <iostream>

#include <glad/glad.h>

static bool s_GLFWInitialized = false;

namespace RocketEngine
{
    Window::Window(const std::string& title, unsigned int width, unsigned int height)
    : m_Title(title), m_Width(width), m_Height(height)
    {
        if (!s_GLFWInitialized)
        {
            if (!InitGLFW())
            {
                std::cout << "Failed to initialize GLFW!" << std::endl;
                return;
            }
            s_GLFWInitialized = true;
        } 

        m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (!m_Window)
        {
            std::cout << "Failed to create window!" << std::endl;
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_Window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize Glad!" << std::endl;
        }

        std::cout << "OpenGL Info:" << std::endl;
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
        std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;

    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    bool Window::InitGLFW()
    {
        bool state = glfwInit();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        return state;
    }

    void Window::OnUpdate()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}