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
private:
	ModelInstance::ModelInstance* modelInstance = nullptr;
	std::vector<ModelInstance::ModelInstance*> modelInstances;
	std::vector<GameObjectCore*> gameObjects;
public:
	GameObjectManager();
	~GameObjectManager() = default;

	void addGameObject(GameObjectCore* gameObject);

	void removeGameObject(GameObjectCore* gameObject);

	void testPrintGameObjectIDs();

	// this function will create a new game object of the specified type and return a pointer to it.
	// This function will add the pointer to an array
	GameObjectCore* createGameObject(const int _objID, const GameObjectType _objType);

	std::vector<GameObjectCore*>& getGameObjects() { return gameObjects; }

private:
	void createModelInstance(const int _objID, const GameObjectType _objType);
	ModelInstance::ModelInstance* createModelInstance(const int _objID, const char* _modelName, const GameObjectType _objType);
};

