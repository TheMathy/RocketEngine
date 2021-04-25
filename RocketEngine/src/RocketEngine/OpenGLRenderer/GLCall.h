#pragma once

#define ASSERT(x) if (!(x)) __builtin_debugtrap();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

namespace RocketEngine
{
    void GLClearError();
    bool GLLogCall(const char* function, const char* file, int line);
}