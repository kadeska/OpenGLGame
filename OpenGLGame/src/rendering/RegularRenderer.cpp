#include <iostream>
#include <chrono>
//#include <reactphysics3d/reactphysics3d.h>
#include "../glfw/glfwIncludes.hpp"

#include "RegularRenderer.hpp"
#include "../glfw/glfwWindow.hpp"


RegularRenderer::RegularRenderer(OpenGLGame::GlfwWindow* window, Scene* _scene)
{
    //previousFrameTime = getCurrentSystemTime(); 
    //accumulator = 0.0L;
	scene = _scene;
	//sceneManager = new SceneManager();
    //scene = sceneManager->createDefaultScene();

}

// update physics sim and render the scene.
void RegularRenderer::render(OpenGLGame::GlfwWindow* window, Scene* _scene, float _timestep, float _factor)
{
    // move this back into the window class
    glfwSetInputMode(window->get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // put this here so the mouse is only captured when we want to actually start rendering.


    setScenePtr(_scene);

    // input
    processInput(window->get());

    // render the frame (render() will perform its own scene update if present)
    if (shouldRender && _scene != nullptr)
    {
        scene->updatePhysicsWorld(_timestep, _factor);
        window->render();
        //render();
        glfwSwapBuffers(window->get());
    } else {
        // if the scene pointer is nullptr then there is nothing to render, so we should just render an empty screen or a debug message.
        window->renderBlank();
        glfwSwapBuffers(window->get());
        //return;
    }

    glfwPollEvents();
}