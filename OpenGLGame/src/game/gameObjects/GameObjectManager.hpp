#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include "GameObjectCore.hpp"
#include <functional>




//This class will be where I store and manage all game objects. 
// 
class GameObjectManager
{
	std::vector<ModelInstance::ModelInstance*> modelInstances;
	std::vector<GameObjectCore*> gameObjects;
public:
	GameObjectManager();
	~GameObjectManager() = default;

	void addGameObject(GameObjectCore* gameObject);

	void removeGameObject(GameObjectCore* gameObject);

	void testPrintGameObjectIDs()
	{
		std::for_each(gameObjects.begin(), gameObjects.end(),
			[](GameObjectCore* obj) {
				if (obj) obj->printID();
			});
	}

	// this function will create a new game object of the specified type and return a pointer to it.
	// This function will add the pointer to an array
	GameObjectCore* createGameObject(const int _objID, const GameObjectType _objType)
	{
		ModelInstance::ModelInstance* modelInstance = new ModelInstance::ModelInstance("default", rp3d::Vector3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), true);
		modelInstances.push_back(modelInstance);
		GameObjectCore* newGameObject = new GameObjectCore(modelInstance);
		addGameObject(newGameObject);
		return newGameObject;
	}
};

