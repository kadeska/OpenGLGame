#include "GameObjectBase.hpp"


void GameObjectBase::init(rp3d::PhysicsCommon* _physicsCommon, GameObjectType type)
{
	this->physicsCommon = _physicsCommon;
	this->gameObjectType = type;
}

void GameObjectBase::setCollisionShape(rp3d::CollisionShape* shape)
{
	//modelInstance->collisionShape = shape;
}
