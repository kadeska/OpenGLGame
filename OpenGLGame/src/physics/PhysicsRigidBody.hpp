#pragma once
#include <reactphysics3d/mathematics/Transform.h>
#include <reactphysics3d/body/RigidBody.h>
class PhysicsRigidBody
{
private:
	reactphysics3d::RigidBody* rigidBodyPtr = nullptr;
	reactphysics3d::PhysicsWorld* physicsWorldPtr = nullptr;
	// Initial position and orientation of the rigid body
	reactphysics3d::Vector3 position = reactphysics3d::Vector3(0.0, 3.0, 0.0);
	reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
	reactphysics3d::Transform* transform = new reactphysics3d::Transform(position, orientation);

public:
	PhysicsRigidBody(reactphysics3d::PhysicsWorld* physicsWorldPtr);
	~PhysicsRigidBody() = default;
private:
	void createRigidBody(reactphysics3d::Transform* transform);
};

