#pragma once
#include "GameObjectBase.hpp"
#include <reactphysics3d/mathematics/Vector3.h>
class Ground : public GameObjectBase
{
private:
	const rp3d::Vector3 halfExtents = rp3d::Vector3(2.0f, 3.0f, 5.0f);
public:
	Ground() 
	{
		init(physicsCommon, GameObjectType::GROUND);
		setCollisionShape(physicsCommon->createBoxShape(halfExtents));
	}
};

