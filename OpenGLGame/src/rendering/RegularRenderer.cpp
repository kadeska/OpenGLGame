#include <iostream>
#include <chrono>
//#include <reactphysics3d/reactphysics3d.h>
#include "../glfw/glfwIncludes.hpp"

#include "RegularRenderer.hpp"
#include "../glfw/glfwWindow.hpp"


RegularRenderer::RegularRenderer(OpenGLGame::GlfwWindow* window)
{
    previousFrameTime = getCurrentSystemTime(); 
    accumulator = 0.0L;
	sceneManager = new SceneManager();
    scene = sceneManager->createDefaultScene();

}

// update physics sim and render the scene.
void RegularRenderer::render(OpenGLGame::GlfwWindow* window)
{
    // move this back into the window class
    glfwSetInputMode(window->get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // put this here so the mouse is only captured when we want to actually start rendering.

    

    while (!glfwWindowShouldClose(window->get()))
    {
        // Constant physics time step
        const float timestep = 1.0f / 60.0f;

        // Get the current system time
        long double currentFrameTime = getCurrentSystemTime();

        // Compute the time difference between the two frames
        long double frameDeltaTime = currentFrameTime - previousFrameTime;
        previousFrameTime = currentFrameTime;

        // Add the time difference in the accumulator
        accumulator += frameDeltaTime;

        // Step the physics simulation for all fixed timesteps
        while (accumulator >= timestep)
        {
            // Perform the physics simulation step (no interpolation during stepping)
            scene->updatePhysicsWorld(timestep, 1.0f);

            accumulator -= timestep;
        }

        // Calculate the interpolation factor for rendering
        // This represents how far into the next physics timestep we are
        // factor = 0.0 means we're at the previous physics frame
        // factor = 1.0 means we're at the current physics frame (shouldn't reach exactly 1.0)
        float renderFactor = accumulator / timestep;




        // Now you can render your body using the new transform



        // update deltaTime used for camera movement/input
        deltaTime = static_cast<float>(frameDeltaTime);

        // input
        processInput(window->get());

        // render the frame (render() will perform its own scene update if present)
        if (shouldRender)
        {
            window->render();
            //render();
            glfwSwapBuffers(window->get());
        }

        glfwPollEvents();
    }
}