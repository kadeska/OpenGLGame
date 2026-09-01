#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include "../model/ModelInstance.hpp"

enum class GameObjectType 
{
	// ground and player
	GROUND,
	PLAYER,
	// Entities
	ENEMY,
	ITEM,

};

class GameObjectBase
{
public:
	GameObjectType gameObjectType;
	// The game objects rigid body if applicable.
	rp3d::RigidBody* rigidBody;
	ModelInstance::ModelInstance* modelInstance;

	// the pointer to the physics common object
	rp3d::PhysicsCommon* physicsCommon;

	// The collision shape
	rp3d::CollisionShape* collisionShape;

	// I dont need to do anything with position as that is managed by the physics manager
	//void updateTransform();


	void init(rp3d::PhysicsCommon* _physicsCommon, GameObjectType type);

	void setCollisionShape(rp3d::CollisionShape* shape);

};

