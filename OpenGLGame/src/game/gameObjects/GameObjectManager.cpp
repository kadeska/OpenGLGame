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
void GameObjectManager::removeGameObject(GameObjectCore* gameObject)
{
}
void GameObjectManager::testPrintGameObjectIDs()
{
	std::for_each(gameObjects.begin(), gameObjects.end(),
		[](GameObjectCore* obj) {
			if (obj) obj->printID();
		});
}
GameObjectCore* GameObjectManager::createGameObject(const int _objID, const GameObjectType _objType)
{
	// create a model instance for the game object
	// this should be determined by the game object type. I can use a switch statement.
	//
	createModelInstance(_objID, _objType);
	// add the model instance to the managers array of instances.
	modelInstances.push_back(modelInstance);
	// create a new game object core with the model instance
	GameObjectCore* newGameObject = new GameObjectCore(modelInstance);
	// add the game object to the managers array of game objects.
	addGameObject(newGameObject);

	// return the pointer to the new game object.
	// This can be used if I want to do something with the game object after it is created, such as adding components to it.
	// even though I add the game object to an array for storage and I could just access it from the array with the id, but this seems like a better method since its all just pointers to memory.
	return newGameObject;
}

void GameObjectManager::createModelInstance(const int _objID, const GameObjectType _objType)
{
	switch (_objType)
	{
	case GameObjectType::PLAYER:
		modelInstance = createModelInstance(_objID, "player", _objType);
		break;
	case GameObjectType::COLLIDABLE:
		modelInstance = createModelInstance(_objID, "collidable", _objType);
		break;
	case GameObjectType::ENEMY:
		modelInstance = createModelInstance(_objID, "enemy", _objType);
		break;
	case GameObjectType::ITEM:
		modelInstance = createModelInstance(_objID, "item", _objType);
		break;
	default:
		break;
	}
}

ModelInstance::ModelInstance* GameObjectManager::createModelInstance(const int _objID, const char* _modelName, const GameObjectType _objType)
{
	return new ModelInstance::ModelInstance(_objID, _modelName, _objType, rp3d::Vector3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), true);
}
