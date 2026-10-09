#pragma once
#include "../physics/PhysicsManager.hpp"
#include "../scene/SceneManager.hpp"
#include "../rendering/RenderManager.hpp"

#include "../glfw/glfwWindow.hpp"

#include "../utils/Logger.hpp"
using namespace logger;


class GameManager
{
private:
	PhysicsManager* physicsManager = nullptr;
	SceneManager* sceneManager = nullptr;
	RenderManager* renderManager = nullptr;
	
	//Scene* activeScene = nullptr;

	long double previousFrameTime;
	long double accumulator;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	void timeStepPhysics(Scene* _scene, float timestep, float factor);

public:
	GameManager();
	~GameManager();

	// initialize the game manager with a GLFW window.
	void init(OpenGLGame::GlfwWindow* _window);
	// this will initialize the scenes and start the renderer.
	void startGame();
	void startRenderer();
};

