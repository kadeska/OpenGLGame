#include "GameObjectManager.hpp"

GameObjectManager::GameObjectManager()
{
}

void GameObjectManager::addGameObject(GameObjectCore* gameObject)
{
	if (!gameObject) 
	{
		std::cerr << "Error: Attempted to add a null game object to the manager." << std::endl;
		return;
	}
	gameObjects.push_back(gameObject);
}
