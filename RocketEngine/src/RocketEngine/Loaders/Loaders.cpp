#include "RocketEngine/Loaders/Loaders.h"

#include <fstream>
#include <sstream>

#include "RocketEngine/DebuggingTools/ScopeTimer.h"

namespace RocketEngine
{
    std::shared_ptr<Mesh> Loaders::LoadObjFileImp(const std::string& filePath)
    {
        RocketEngine::DebuggingTools::ScopeTimer scopeTimer;
        std::fstream fileStream(filePath);
        std::string line;

        std::stringstream stringStream;
        
        std::string prefix = "";

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        // Temporary Vectors
        glm::vec3 tempPosition;

        glm::vec2 tempTextureCoord;
        std::vector<glm::vec2> tempTextureCoords;

        glm::vec3 tempNormal;
        std::vector<glm::vec3> tempNormals;
        
        while (std::getline(fileStream, line))
        {
            stringStream.clear();
            stringStream.str(line);
            
            stringStream >> prefix;

            if (prefix == "v")
            {
                stringStream >> tempPosition.x >> tempPosition.y >> tempPosition.z;

                Vertex vertex(vertices.size(), tempPosition);
                vertices.push_back(vertex);
            }

            else if (prefix == "vt")
            {
                stringStream >> tempTextureCoord.x >> tempTextureCoord.y;
                tempTextureCoords.push_back(tempTextureCoord);
            }

            else if (prefix == "vn")
            {
                stringStream >> tempNormal.x >> tempNormal.y >> tempNormal.z;
                tempNormals.push_back(tempNormal);
            }

            else if (prefix == "f")
            {
                unsigned int counter = 0;
                unsigned int index;
                unsigned int ptnIndices[3];

                while(stringStream >> index)
                {
                    ptnIndices[counter] = index - 1;

                    if (stringStream.peek() == '/')
                    {
                        stringStream.ignore(1, '/');
                    }

                    if (counter >= 2)
                    {
                        ProcessVertex(ptnIndices, vertices, indices);

                        if (stringStream.peek() == ' ')
                            stringStream.ignore(1, ' ');
                        counter = 0;
                        continue;
                    }

                    counter++;

                }
            }    
        }
        
        RemoveUnusedVertices(vertices);
        float verticesArray[vertices.size() * 8];

        unsigned int indicesArray[indices.size()];

        ConvertDataToArray(vertices, tempTextureCoords, tempNormals, verticesArray);
        ConvertIndicesToArray(indices, indicesArray);
        
        std::shared_ptr<Mesh> mesh(new Mesh(verticesArray, vertices.size() * 8 * sizeof(float), indicesArray, indices.size()));

        return mesh;
    }

    void Loaders::ProcessVertex(const unsigned int* ptnIndices, std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
    {
        unsigned int index = ptnIndices[0];

        Vertex& currentVertex = vertices[index];

        unsigned int textureCoordIndex = ptnIndices[1];
        unsigned int normalIndex = ptnIndices[2];

        if (!currentVertex.isSet())
        {
            currentVertex.SetTextureIndex(textureCoordIndex);
            currentVertex.SetNormalIndex(normalIndex);
            indices.push_back(index);
        }
        else
        {
            DealWithAlreadyProcessedVertex(currentVertex, textureCoordIndex, normalIndex, indices, vertices);
        }
    }

    void Loaders::DealWithAlreadyProcessedVertex(Vertex& previousVertex, int newTextureIndex, int newNormalIndex, std::vector<unsigned int>& indicies, std::vector<Vertex>& verticies)
    {
        if (previousVertex.hasSameTextureAndNormal(newTextureIndex, newNormalIndex))
        {
            indicies.push_back(previousVertex.GetIndex());
            return;
        }
        else
        {
            std::shared_ptr<Vertex> anotherVertex = previousVertex.GetDuplicateVertex();
            if (anotherVertex != nullptr)
            {
                DealWithAlreadyProcessedVertex(*anotherVertex, newTextureIndex, newNormalIndex, indicies, verticies);
                return;
            }
            else
            {
                Vertex duplicateVertex(verticies.size(), previousVertex.GetPositon());
                duplicateVertex.SetTextureIndex(newTextureIndex);
                duplicateVertex.SetNormalIndex(newNormalIndex);
                previousVertex.SetDuplicateVertex(duplicateVertex);
                verticies.push_back(duplicateVertex);
                indicies.push_back(duplicateVertex.GetIndex());
            }
        }
    }

    void Loaders::RemoveUnusedVertices(std::vector<Vertex>& vertices)
    {
        for (Vertex vertex : vertices)
        {
            vertex.avarageTangents();
            if (!vertex.isSet())
            {
                vertex.SetTextureIndex(0);
                vertex.SetNormalIndex(0);
            }
        }
    }

    void Loaders::ConvertIndicesToArray(const std::vector<unsigned int>& indices, unsigned int* indicesArray)
    {
        for (unsigned int i = 0; i < indices.size(); i++)
        {
            indicesArray[i] = indices[i];
        }
    }

    void Loaders::ConvertDataToArray(const std::vector<Vertex>& vertices, const std::vector<glm::vec2>& textureCoords, const std::vector<glm::vec3>& normals, float* vetricesArray)
    {
        glm::vec3 position;
        glm::vec2 textureCoord;
        glm::vec3 normal;

        for (unsigned int i = 0; i < vertices.size(); i++)
        {
            Vertex currentVertex = vertices[i];

            position = currentVertex.GetPositon();

            int textureIndex = currentVertex.GetTextureIndex();
            if (textureIndex < 0)
                textureIndex = 0; 

            textureCoord = textureCoords[textureIndex];
            normal = normals[currentVertex.GetNormalIndex()];

            vetricesArray[i * 8] = position.x;
            vetricesArray[i * 8 + 1] = position.y;
            vetricesArray[i * 8 + 2] = position.z;

            vetricesArray[i * 8 + 3] = textureCoord.x;
            vetricesArray[i * 8 + 4] = textureCoord.y;

            vetricesArray[i * 8 + 5] = normal.x;
            vetricesArray[i * 8 + 6] = normal.y;
            vetricesArray[i * 8 + 7] = normal.z;
        }
    }
}