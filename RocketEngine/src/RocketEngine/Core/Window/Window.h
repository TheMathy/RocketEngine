#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace RocketEngine
{
    class Window
    {
    public:
        Window(const std::string& title, unsigned int width, unsigned int height);
        ~Window();

        void OnUpdate();

        inline void* GetNativeWindow() const { return m_Window; }
        inline unsigned int GetWidth() const { return m_Width; }
        inline unsigned int GetHeight() const { return m_Height; }

    private:
        GLFWwindow* m_Window;
        std::string m_Title;
        unsigned int m_Width, m_Height;

        bool InitGLFW();
    };
}