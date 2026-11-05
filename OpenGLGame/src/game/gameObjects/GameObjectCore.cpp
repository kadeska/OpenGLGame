#include "GameObjectCore.hpp"

GameObjectCore::GameObjectCore(ModelInstance::ModelInstance* modelInstance)
{
	// Core components will get initialized when a game object is created in their respective constructors.
	components.pointers.modelInstance = modelInstance;
}

void GameObjectCore::printID()
{
	std::cout << "GameObject ID: " << id << std::endl;
}
