#include "GameObjectBase.hpp"


void GameObjectBase::init(GameObjectType type)
{
	gameObjectType = type;
}

void GameObjectBase::setCollisionShape(rp3d::CollisionShape* shape)
{
	//modelInstance->collisionShape = shape;
}
