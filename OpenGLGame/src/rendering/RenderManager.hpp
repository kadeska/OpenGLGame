#pragma once
#include "../glfw/glfwWindow.hpp"
#include "RegularRenderer.hpp"
#include "DebugRenderer.hpp"


class RenderManager
{
private:
	OpenGLGame::GlfwWindow* window = nullptr;
public:
	bool debugRender = false;

	RegularRenderer* regularRenderer = nullptr;
	DebugRenderer* debugRenderer = nullptr;



	RenderManager(OpenGLGame::GlfwWindow* window);
	void render(Scene* _scene, float _timestep, float _factor);
	void setDebugRender(bool value);
};

