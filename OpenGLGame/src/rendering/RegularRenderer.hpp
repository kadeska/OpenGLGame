#pragma once

#include "../scene/SceneManager.hpp"
#include "../glfw/glfwWindow.hpp"

class RegularRenderer
{
public:
	long double previousFrameTime;
	long double accumulator;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	SceneManager* sceneManager = nullptr;
	Scene* scene = nullptr;

	// signals
	bool shouldRender = true;


	RegularRenderer(OpenGLGame::GlfwWindow* window);

	void render(OpenGLGame::GlfwWindow* window);
	// Returns current system time in seconds (high-resolution) as a long double.
	static long double getCurrentSystemTime()
	{
		using namespace std::chrono;
		return duration_cast<duration<long double>>(high_resolution_clock::now().time_since_epoch()).count();
	}
};

