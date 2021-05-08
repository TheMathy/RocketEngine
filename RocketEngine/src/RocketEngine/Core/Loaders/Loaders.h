#pragma once

#include <string>
#include <memory>
#include <vector>

#include "glm/glm.hpp"

#include "RocketEngine/Core/Loaders/Vertex.h"

#include "RocketEngine/Core/OpenGLRenderer/Shader.h"
#include "RocketEngine/Core/OpenGLRenderer/Texture.h"
#include "RocketEngine/Core/Components/Mesh.h"

namespace RocketEngine
{
    class Loaders
    {
    private:
        Loaders() {}
    public:
        Loaders(const Loaders&) = delete;
        static Loaders& Get() { static Loaders s_Instance; return s_Instance; }
    public:
        static ShaderSources LoadShader(const std::string& filePath) { return Get().LoadShaderImp(filePath); }
        static Image LoadImage(const std::string& filePath) { return Get().LoadImageImp(filePath); }
        static std::shared_ptr<Mesh> LoadObjFile(const std::string& filePath) { return Get().LoadObjFileImp(filePath); }

    private:
        // Shader
        ShaderSources LoadShaderImp(const std::string& filePath);

        //Texture
        Image LoadImageImp(const std::string& filePath);

        // ObjFileLoader
        std::shared_ptr<Mesh> LoadObjFileImp(const std::string& filePath);
        void ProcessVertex(const unsigned int* ptnIndices, std::vector<Vertex>& verticies, std::vector<unsigned int>& indices);
        static void DealWithAlreadyProcessedVertex(Vertex& previousVertex, int newTextureIndex, int newNormalIndex, std::vector<unsigned int>& indicies, std::vector<Vertex>& verticies);
        static void RemoveUnusedVertices(std::vector<Vertex>& vertices);
        static void ConvertIndicesToArray(const std::vector<unsigned int>& indices, unsigned int* indicesArray);
        static void ConvertDataToArray(const std::vector<Vertex>& vertices, const std::vector<glm::vec2>& textureCoords, const std::vector<glm::vec3>& normals, float* vetricesArray);
    };
}