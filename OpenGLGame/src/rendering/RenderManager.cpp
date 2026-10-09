#include "RenderManager.hpp"



RenderManager::RenderManager(OpenGLGame::GlfwWindow* _window)
{
	regularRenderer = new RegularRenderer(_window, nullptr);
	debugRenderer = new DebugRenderer(_window);
	window = _window;
}

// starts the render loop. 
void RenderManager::render(Scene* _scene, float _timestep, float _factor)
{
	if (debugRender)
	{
		//debugRenderer->render(physycsDebugRenderer, view, projection);
	}
	else
	{
		regularRenderer->render(window, _scene, _timestep, _factor);
	}
}

void RenderManager::setDebugRender(bool value)
{
	debugRender = value;
}