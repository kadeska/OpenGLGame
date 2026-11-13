#include <iostream>
#include <chrono>

#include "GameManager.hpp"

// Constant physics time step
const float timestep = 1.0f / 60.0f;
float factor;

static long double getCurrentSystemTime();

OpenGLGame::GlfwWindow* window = nullptr;
bool sceneReady;

void GameManager::timeStepPhysics(Scene* activeScene,float timestep, float _factor)
{
    factor = _factor;

    // only do time step and render if the scene is ready.
    if (!sceneReady) return;

    // Get the current system time
    long double currentFrameTime = getCurrentSystemTime();
    previousFrameTime = currentFrameTime;
	accumulator = 0.0L;

    // Compute the time difference between the two frames
    long double frameDeltaTime = currentFrameTime - previousFrameTime;
    

    // Add the time difference in the accumulator
    accumulator += frameDeltaTime;

    // Step the physics simulation for all fixed timesteps
    while (accumulator >= timestep)
    {
        //Scene* activeScene = sceneManager->getActiveScene();
        if (!activeScene && !activeScene->getIsGameScene())
        {
            //log("No active scene or not a game scene.", LogType::ERROR);
            break;
        }
        else
        {
            // Perform the physics simulation step (no interpolation during stepping)
            //sceneManager->getActiveScene()->updatePhysicsWorld(timestep, sceneManager->getActiveScene()->getPhysicsWorld());
            // pass in the physics manager to the updatePhysicsWorld function so we can use the physics manager update function for the scene's physics world.
            activeScene->updatePhysicsWorld(timestep, physicsManager);

            accumulator -= timestep;
        }
    }

    // Calculate the interpolation factor for rendering
    // This represents how far into the next physics timestep we are
    // factor = 0.0 means we're at the previous physics frame
    // factor = 1.0 means we're at the current physics frame (shouldn't reach exactly 1.0)
    factor = accumulator / timestep;

    // Now you can render your body using the new transform
    activeScene->updateModelsFromPhysicsWorld(activeScene->getPhysicsWorld(), factor);

    // update deltaTime used for camera movement/input
    deltaTime = static_cast<float>(frameDeltaTime);
}

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

// Bind the window to the renderer, initialize the physics and scene managers.
void GameManager::init(OpenGLGame::GlfwWindow* _window)
{
	window = _window;
    // I dont want to have a global physics manager to allow each scene to have their own physics world.
	//physicsManager = new PhysicsManager();
	renderManager = new RenderManager(window);
	physicsManager = new PhysicsManager();
	sceneManager = new SceneManager(physicsManager);
}


void GameManager::startGame()
{
    
	// This is where the main game loop goes.
	// Start by initializing all the required scenes and any other game systems. 
	// A scene is a collection of model instances and other game objects needed to render a specific game level or the main menu. 

    // load and initialize the main menu scene and the default game scene.
	sceneManager->initializeScenes(); // sceneManager->createDefaultScene();
	//startRenderer();


    if (!sceneManager->getActiveScene()) 
    {
        log("No active scene! ------", LogType::ERROR);
    }

    //previousFrameTime = getCurrentSystemTime();
    accumulator = 0.0L;

	// main game loop. 
	while (!glfwWindowShouldClose(window->get())) 
	{
        //log("Active scene is ready.", LogType::INFO);
        sceneReady = true;

        timeStepPhysics(sceneManager->getActiveScene(), timestep, factor);
        renderManager->render(sceneManager->getActiveScene(), timestep, factor);
	}

}

void GameManager::startRenderer()
{
}


// Returns current system time in seconds (high-resolution) as a long double.
static long double getCurrentSystemTime()
{
    using namespace std::chrono;
    return duration_cast<duration<long double>>(high_resolution_clock::now().time_since_epoch()).count();
}