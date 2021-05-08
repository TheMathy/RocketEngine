#include "RocketEngine/Core/OpenGLRenderer/Texture.h"

#include <glad/glad.h>

#include <stb_image.h>

#include "RocketEngine/Core/OpenGLRenderer/GLCall.h"

namespace RocketEngine
{
    void Image::ClearLocalBuffer()
    {
        if (localBuffer)
            stbi_image_free(localBuffer);
    }

    Texture::Texture(Image image)
        : m_RendererID(0)
    {
        GLCall(glGenTextures(1, &m_RendererID));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.localBuffer));
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));

        image.ClearLocalBuffer();
    }

    Texture::~Texture()
    {
        GLCall(glDeleteTextures(1, &m_RendererID));
    }

    void Texture::Bind(unsigned int slot /*= 0*/) const
    {
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    }

    void Texture::Unbind() const
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }
}