#pragma once
#include  "GameObjectBase.hpp"
class Player : public GameObjectBase
{
public:
	// health points
	float hp = 100.0f;
	// defence points
	float dp = 0.0f;
	// crit chance
	float critChance = 0.0f;
	// crit damage multiplier
	float critDamageMultiplier = 1.35f;

public:
	Player() 
	{
		init(physicsCommon, GameObjectType::PLAYER);
		setCollisionShape(physicsCommon->createCapsuleShape(2.0, 3.0));
	}

};

