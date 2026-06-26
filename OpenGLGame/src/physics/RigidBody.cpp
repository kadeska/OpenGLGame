#include "RigidBody.hpp"
#include <stdio.h>

rp3d::RigidBody* rigidBodyPtr;
rp3d::SphereShape* sphereShape;    // store shapes so you can destroy later

int modelPtrIndex;

RigidBody::RigidBody(rp3d::Vector3 position, rp3d::PhysicsWorld* world, int model_ptr_index)
{
	std::cout << "Initializing rigid body.\n";

	modelPtrIndex = model_ptr_index;

	// Initial position and orientation of the rigid body
	//rp3d::Vector3 pos(0.0, 3.0, 0.0);
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();
	rp3d::Transform _transform(position, orientation);

	transform = _transform;



	if(!world) {
		std::cerr << "Error: Physics world pointer is null. Cannot create rigid body." << std::endl;
		return;
	}

	// Create a rigid body in the world
	rigidBodyPtr = world->createRigidBody(transform);
	rigidBodyPtr->setType(rp3d::BodyType::DYNAMIC);
	rigidBodyPtr->setMass(0.001f);
	rigidBodyPtr->enableGravity(true);
	rigidBodyPtr->setLinearDamping(0.9f);
}

void RigidBody::move(rp3d::Vector3 newPosition)
{
	std::cout << "Moving rigid body to new position: (" << newPosition.x << ", " <<
		newPosition.y << ", " << newPosition.z << ")" << std::endl;

	rigidBodyPtr->setTransform(rp3d::Transform(newPosition, rp3d::Quaternion::identity()));
}

rp3d::RigidBody* RigidBody::getRigidBodyPtr()
{
	if (rigidBodyPtr == nullptr) 
	{
		std::cerr << "Error: Rigid body pointer is null." << std::endl;
		return nullptr;
	}
	return rigidBodyPtr;
}
