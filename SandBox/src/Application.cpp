#include <iostream>

#include "RocketEngine/Core/Window/Window.h"

#include "RocketEngine/Core/MasterRenderer/MasterRenderer.h"
#include "RocketEngine/Core/Loaders/Loaders.h"
#include "RocketEngine/Core/Input/Input.h"

#include "RocketEngine/Terrain/Terrain.h"

int main()
{
    // "using namespace RocketEngine" is possible but it is not used for better visibility

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
    RocketEngine::GameObject object(RocketEngine::Transform(glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.25f, 0.25f, 0.25f)), mesh, material);
    // Create new RocketEngine Terrain
    RocketEngine::Terrain terrain(RocketEngine::Transform(glm::vec3(-1.5f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), material, 3.0f, 16);

    // Create new RocketEngine Camera
    RocketEngine::Camera camera(window, glm::vec4(153.0f, 204.0f, 255.0f, 255.0f), 70.0f, 0.1f, 1000.0f);
    // Create new RocketEngine LightSource
    RocketEngine::LightSource lightSource(RocketEngine::Transform(glm::vec3(0.0f, 1.0f, 1.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));


    // Create new Renderer Context
    RocketEngine::MasterRenderer renderer;
    // Prepare Renderer for Rendering
    renderer.Prepare();

    // One time possition update
    camera.transform.position.y = 0.5f;
    camera.transform.position.z = 5.0f;

    while (!glfwWindowShouldClose(static_cast<GLFWwindow*>(window.GetNativeWindow())))
    {
        // ---APPLICATION ON UPDATA---
        // Example of keyboard input
        if (RocketEngine::Input::KeyPressed(RocketEngine::KeyCode::Space))
        {
            // Increment object's y rotation
            object.transform.rotation.y += 1.0f;
        }

        // Example of mouse input
        if (RocketEngine::Input::MouseButtonPressed(RocketEngine::MouseCode::ButtonLeft))
        {
            // Increment object's x rotation
            object.transform.rotation.x += 1.0f;
            // Log mouse position
            std::cout << RocketEngine::Input::MousePosition().x << " " << RocketEngine::Input::MousePosition().y << std::endl;
        }
            
        // ---RENDERING---
        // Clear Screen
        renderer.Clear(camera.backgroundColor);
        // Add Object to Render Queue
        renderer.Submit(terrain);
        renderer.Submit(object);
        // Render Scane with all submited objects, camera and light source
        // Soon will be changed to take only one Scene as a argument
        renderer.RenderScene(camera, lightSource);

        //Uptade windows
        window.OnUpdate();
    }
}