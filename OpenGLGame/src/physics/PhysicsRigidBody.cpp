#include "PhysicsRigidBody.hpp"
#include <reactphysics3d/engine/PhysicsWorld.h>
#include "../utils/Logger.hpp"

using namespace logger;

PhysicsRigidBody::PhysicsRigidBody(reactphysics3d::PhysicsWorld* _physicsWorldPtr)
{
	this->physicsWorldPtr = _physicsWorldPtr;
	
	createRigidBody(transform);
}

void PhysicsRigidBody::createRigidBody(reactphysics3d::Transform* transform)
{
	this->rigidBodyPtr = physicsWorldPtr->createRigidBody(*transform);
	//std::cout << "PhysicsRigidBody created." << std::endl;
	log("PhysicsRigidBody created.", LogType::DEBUG);	
}

