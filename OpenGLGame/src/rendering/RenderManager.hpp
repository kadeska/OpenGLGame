#pragma once
#include "../glfw/glfwWindow.hpp"
#include "RegularRenderer.hpp"
#include "DebugRenderer.hpp"


class RenderManager
{
public:
	bool debugRender = false;

	RegularRenderer* regularRenderer = nullptr;
	DebugRenderer* debugRenderer = nullptr;



	RenderManager(OpenGLGame::GlfwWindow* window);
	void render();
	void setDebugRender(bool value);
};

