#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>

class RigidBody
{
	// initialize a new rigid body with the given parameters.
public:
	rp3d::Transform transform;
	RigidBody(rp3d::Vector3 position, rp3d::PhysicsWorld* world);
	~RigidBody() = default;
	void move(rp3d::Vector3 newPosition);
	rp3d::RigidBody* getRigidBodyPtr();

};

