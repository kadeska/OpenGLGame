#include "GameManager.hpp"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::init(OpenGLGame::GlfwWindow* _window)
{
	renderManager = new RenderManager(_window);
	sceneManager = new SceneManager();
	activeScene = sceneManager->createDefaultScene();
}

void GameManager::update()
{
	renderManager->render();
}
