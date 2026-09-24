#pragma once
//#include "../physics/PhysicsManager.hpp"
#include "../rendering/RenderManager.hpp"
#include "../scene/SceneManager.hpp"
#include "../glfw/glfwWindow.hpp"


class GameManager
{
private:
	RenderManager* renderManager = nullptr;
	SceneManager* sceneManager = nullptr;
	Scene* activeScene = nullptr;
public:
	GameManager();
	~GameManager();

	void init(OpenGLGame::GlfwWindow* _window);
	void update();
	void render();
};

