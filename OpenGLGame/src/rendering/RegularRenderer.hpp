#pragma once

#include "../scene/SceneManager.hpp"
#include "../glfw/glfwWindow.hpp"

class RegularRenderer
{
public:
	//long double previousFrameTime;
	//long double accumulator;

	//float deltaTime = 0.0f;
	//float lastFrame = 0.0f;

	//SceneManager* sceneManager = nullptr;
	Scene* scene = nullptr;

	// signals
	bool shouldRender = true;


	RegularRenderer(OpenGLGame::GlfwWindow* window, Scene* _scene);

	void render(OpenGLGame::GlfwWindow* window, Scene* scene, float timestep, float renderFactor);
	

	void setScenePtr(Scene* _scene) {
		scene = _scene;
	}
};

