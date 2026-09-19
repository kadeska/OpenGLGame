#include "RenderManager.hpp"

OpenGLGame::GlfwWindow* window = nullptr;

RenderManager::RenderManager(OpenGLGame::GlfwWindow* _window)
{
	regularRenderer = new RegularRenderer(_window);
	debugRenderer = new DebugRenderer(_window);
	window = _window;
}

void RenderManager::render()
{
	if (debugRender)
	{
		//debugRenderer->render(physycsDebugRenderer, view, projection);
	}
	else
	{
		regularRenderer->render(window);
	}
}

void RenderManager::setDebugRender(bool value)
{
	debugRender = value;
}
