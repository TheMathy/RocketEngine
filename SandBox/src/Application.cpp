#include <iostream>

#include "RocketEngine/Core/Window/Window.h"

#include "RocketEngine/Core/MasterRenderer/MasterRenderer.h"
#include "RocketEngine/Core/Loaders/Loaders.h"

int main()
{
    // Create new RocketEngine Window
    RocketEngine::Window window("SandBox", 1920.0f, 1080.0f);

    // Load shader
    std::shared_ptr<RocketEngine::Shader> shader = std::make_shared<RocketEngine::Shader>(RocketEngine::Loaders::LoadShader("SandBox/Assets/Shaders/Main.shader"));
    // Load texture
    std::shared_ptr<RocketEngine::Texture> texture = std::make_shared<RocketEngine::Texture>(RocketEngine::Loaders::LoadImage("SandBox/Assets/Textures/Texture.png"));
    // Create RocketEngine Mesh
    std::shared_ptr<RocketEngine::Mesh> mesh = RocketEngine::Loaders::LoadObjFile("SandBox/Assets/Models/Cube.obj");
    // Create RocketEngine Material
    std::shared_ptr<RocketEngine::Material> material = std::make_shared<RocketEngine::Material>(shader, texture);

    // Every shader, texture, mesh or material in memory should be stored as shared pointer

    // Create new RocketEngine Object
    RocketEngine::GameObject object(RocketEngine::Transform(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), mesh, material);
    // Create new RocketEngine Camera
    RocketEngine::Camera camera(window, glm::vec4(153.0f, 204.0f, 255.0f, 255.0f), 70.0f, 0.1f, 1000.0f);
    // Create new RocketEngine LightSource
    RocketEngine::LightSource lightSource(RocketEngine::Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // Create new Renderer Context
    RocketEngine::MasterRenderer renderer;
    // Prepare Renderer for Rendering
    renderer.Prepare();

    while (!glfwWindowShouldClose(static_cast<GLFWwindow*>(window.GetNativeWindow())))
    {
        // ---APPLICATION ON UPDATA---
        // Update object rotation
        object.transform.rotation.x += 1.0f;
        object.transform.rotation.z += 1.0f;

        // ---RENDERING---
        // Clear Screen
        renderer.Clear(camera.backgroundColor);
        // Add Object to Render Queue
        renderer.Submit(object);
        // Render Scane with all submited objects, camera and light source
        // Soon will be changed to take only one Scene as a argument
        renderer.RenderScene(camera, lightSource);

        //Uptade windows
        window.OnUpdate();
    }
}