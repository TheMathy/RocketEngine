#include "RocketEngine/MasterRenderer/MasterRenderer.h"

#include <memory>

#include <glad/glad.h>

#include "RocketEngine/OpenGLRenderer/GLCall.h"

namespace RocketEngine
{
    MasterRenderer::MasterRenderer()
    {}

    MasterRenderer::~MasterRenderer()
    {}

    void MasterRenderer::Prepare()
    {
        Renderer::Prepare();
        GLCall(glEnable(GL_CULL_FACE));
        GLCall(glCullFace(GL_BACK));
    }

    void MasterRenderer::Submit(GameObject& gameObject)
    {
        std::shared_ptr<Mesh> mesh = gameObject.GetMesh();
        std::shared_ptr<Material> material = gameObject.GetMaterial();

        if (material == nullptr || mesh == nullptr)
            return;

        std::vector<GameObject*>& batch = m_ObjectMaterialBatch[material];
        batch.push_back(&gameObject);
    }

    void MasterRenderer::RenderScene(Camera& camera, LightSource& lightSource)
    {
        if (m_ObjectMaterialBatch.empty())
            return;

        for ( auto& objectsGroup : m_ObjectMaterialBatch )
        {
            std::shared_ptr<Material> material = objectsGroup.first;

            std::shared_ptr<Shader> shader = material->GetShader();
            shader->Bind();

            material->GetTexture()->Bind();

            std::vector<GameObject*> objects = objectsGroup.second;

            std::shared_ptr<Mesh> mesh = objects[0]->GetMesh();

            mesh->GetVertexArray().Bind();
            mesh->GetIndexBuffer().Bind();

            for ( auto object : objects )
            {
                shader->SetUniformMat4f("u_ProjectionMatrix", camera.GetProjectionMatrix());
                shader->SetUniformMat4f("u_ViewMatrix", camera.GetViewMatrix());
                shader->SetUniformMat4f("u_ModelMatrix", object->transform.GetModelMatrix());

                shader->SetUniform3f("u_lightPosition", lightSource.transform.position.x, lightSource.transform.position.y, lightSource.transform.position.z);
                shader->SetUniform3f("u_lightColor", lightSource.GetColor().x, lightSource.GetColor().y, lightSource.GetColor().z);

                shader->SetUniform1f("u_shineDamper", material->shinyDamper);
                shader->SetUniform1f("u_reflectivity", material->reflectivity);

                GLCall(glDrawElements(GL_TRIANGLES, mesh->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));

                //mesh->GetVertexArray().Unbind();
                //mesh->GetIndexBuffer().Unbind();            
            }
        }
        m_ObjectMaterialBatch.clear();
    }
}


/*
void MasterRenderer::RenderObject(Object& object, Camera& camera, LightSource& lightSource)
{
    
    if (m_Objects.empty())
        return;

    for ( auto objectsGroup : m_Objects )
    {
        std::shared_ptr<Material> material = objectsGroup.first();

        std::shared_ptr<Shader> shader = material->GetShader();
        shader->Bind();

        material->GetTexture()->Bind();

        std::vector<Object&> objects = objectsGroup.second();

        for ( auto object : objects )
        {
            std::shared_ptr<Mesh> mesh = object.GetMesh();

            mesh->GetVertexArray().Bind();
            mesh->GetIndexBuffer().Bind();

            shader->SetUniformMat4f("u_ProjectionMatrix", camera.GetProjectionMatrix());
            shader->SetUniformMat4f("u_ViewMatrix", camera.GetViewMatrix());
            shader->SetUniformMat4f("u_ModelMatrix", object.transform.GetModelMatrix());

            shader->SetUniform3f("u_lightPosition", lightSource.transform.position.x, lightSource.transform.position.y, lightSource.transform.position.z);
            shader->SetUniform3f("u_lightColor", lightSource.GetColor().x, lightSource.GetColor().y, lightSource.GetColor().z);

            shader->SetUniform1f("u_shineDamper", material->shinyDamper);
            shader->SetUniform1f("u_reflectivity", material->reflectivity);

            GLCall(glDrawElements(GL_TRIANGLES, mesh->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));

            mesh->GetVertexArray().Unbind();
            mesh->GetIndexBuffer().Unbind();            
        }

        mesh->GetVertexArray().Unbind();
        mesh->GetIndexBuffer().Unbind();

    }

    std::shared_ptr<Mesh> mesh = object.GetMesh();
    std::shared_ptr<Material> material = object.GetMaterial();

    if (mesh == nullptr)
        return;

    mesh->GetVertexArray().Bind();
    mesh->GetIndexBuffer().Bind();

    std::shared_ptr<Shader> shader = nullptr;

    if (material != nullptr)
    {
        shader = material->GetShader();
        shader->Bind();

        shader->SetUniformMat4f("u_ProjectionMatrix", camera.GetProjectionMatrix());
        shader->SetUniformMat4f("u_ViewMatrix", camera.GetViewMatrix());
        shader->SetUniformMat4f("u_ModelMatrix", object.transform.GetModelMatrix());

        shader->SetUniform3f("u_lightPosition", lightSource.transform.position.x, lightSource.transform.position.y, lightSource.transform.position.z);
        shader->SetUniform3f("u_lightColor", lightSource.GetColor().x, lightSource.GetColor().y, lightSource.GetColor().z);

        shader->SetUniform1f("u_shineDamper", material->shinyDamper);
        shader->SetUniform1f("u_reflectivity", material->reflectivity);

        material->GetTexture()->Bind();
    }
    
    GLCall(glDrawElements(GL_TRIANGLES, mesh->GetIndexBuffer().GetCount(), GL_UNSIGNED_INT, nullptr));
        
    mesh->GetVertexArray().Unbind();
    mesh->GetIndexBuffer().Unbind();

    if (material != nullptr)
    {
        shader->Unbind();
        material->GetTexture()->Unbind();
    }


}
*/
/*
void MasterRenderer::ActivateMaterial(Material& material)
{
    std::shared_ptr<Shader> shader = material.GetShader();
    shader->Bind();
}*/