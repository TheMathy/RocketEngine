#pragma once

#include "glm/glm.hpp"

#include "RocketEngine/Core/Input/KeyCodes.h"
#include "RocketEngine/Core/Input/MouseCodes.h"

namespace RocketEngine
{
    class Input
    {
    private:
        Input() {};
        static Input& Get() { static Input s_Instance; return s_Instance; }
    public:
        Input(const Input&) = delete;
        Input& operator=(const Input&) = delete;
    public:
        static bool KeyPressed(int keycode) { return Get().KeyPressedImpl(keycode); }

        static bool MouseButtonPressed(int button) { return Get().MouseButtonPressedImpl(button); }
        static glm::vec2 MousePosition() { return Get().MousePositionImpl(); }
    private:
        bool KeyPressedImpl(int keycode);

        bool MouseButtonPressedImpl(int button);
        glm::vec2 MousePositionImpl();
    };
}