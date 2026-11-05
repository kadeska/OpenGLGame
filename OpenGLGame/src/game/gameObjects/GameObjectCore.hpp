#pragma once

#include "../../model/ModelInstance.hpp"

// Game Object Core will contain all the core components of any game object. 
//
// The core should contain the following:
// 
// Model Instance pointer
// Flags for active, visible, and collidable
// 
//

enum class GameObjectType
{
	PLAYER, // Player type game object.
	ENEMY, // Enemy type game object.
	ITEM, // Item type game object.
	COLLIDABLE // Collidable type game object, such as the ground, walls, buildings, etc.
};

class GameObjectCore
{
private:
	struct CoreFlags
	{
		bool active = false;
		bool visible = false;
		bool collidable = false;
	};
	struct Pointers
	{
		
		ModelInstance::ModelInstance* modelInstance = nullptr;
	};

public:
	GameObjectCore(ModelInstance::ModelInstance* modelInstance);
	~GameObjectCore() = default;
	
	int id = 0;

	struct CoreComponents
	{
		CoreFlags flags;
		Pointers pointers;
	}components;

	virtual void printID();
};