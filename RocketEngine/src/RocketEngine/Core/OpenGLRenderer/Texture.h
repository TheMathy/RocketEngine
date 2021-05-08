#pragma once

#include <string>

namespace RocketEngine
{
    struct Image
    {
    public:
        unsigned char* localBuffer;
        int width, height;
        int BPP;
    public:
        void ClearLocalBuffer();
    };

    class Texture
    {
    public:
        Texture(Image image);
        ~Texture();

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;
    };
}