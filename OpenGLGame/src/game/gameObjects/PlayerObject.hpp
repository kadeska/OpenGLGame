#pragma once
#include "GameObjectCore.hpp"

class PlayerObject : public GameObjectCore
{
public:
	int health = 100;
	int shield = 100;
	int score = 0;
public:
	PlayerObject(ModelInstance::ModelInstance* modelInstance);
	~PlayerObject() = default;

	virtual void printID() override;
};

