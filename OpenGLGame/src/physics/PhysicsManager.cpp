#include "PhysicsManager.hpp"
#include <reactphysics3d/reactphysics3d.h>
#include <iostream>

#include "PhysicsRigidBody.hpp"

PhysicsManager::PhysicsManager()
{
    std::cout << "PhysiscManager constructor" << std::endl;
    createPhyisicsCommonPtr();
	createPhysicsWorldPtr(getPhysicsCommonPtr());
}

int PhysicsManager::test()
{

    // First you need to create the PhysicsCommon object.
    // This is a factory module that you can use to create physics
    // world and other objects. It is also responsible for
    // logging and memory management
    //reactphysics3d::PhysicsCommon physicsCommon;

    // Create a physics world
    //reactphysics3d::PhysicsWorld* world = physicsCommon->createPhysicsWorld();
    //physicsWorldPtr = physicsCommonPtr->createPhysicsWorld();

    //// Create a rigid body in the world
    //reactphysics3d::Vector3 position(0, 20, 0);
    //reactphysics3d::Quaternion orientation = reactphysics3d::Quaternion::identity();
    //reactphysics3d::Transform transform(position, orientation);
    //reactphysics3d::RigidBody* body = physicsWorldPtr->createRigidBody(transform);

    //const reactphysics3d::decimal timeStep = 1.0f / 60.0f;

    //// Step the simulation a few steps
    //for (int i = 0; i < 20; i++) {

    //    physicsWorldPtr->update(timeStep);

    //    // Get the updated position of the body
    //    const reactphysics3d::Transform& transform = body->getTransform();
    //    const reactphysics3d::Vector3& position = transform.getPosition();

    //    // Display the position of the body
    //    std::cout << "Body Position: (" << position.x << ", " <<
    //        position.y << ", " << position.z << ")" << std::endl;
    //}


    //PhysicsRigidBody rigidbody = PhysicsRigidBody(getPhysicsWorldPtr());


    return 0;
}

//---------------------------------
// TODO: create a logging system
//---------------------------------

reactphysics3d::PhysicsCommon* PhysicsManager::getPhysicsCommonPtr()
{
    if (physicsCommonPtr == nullptr)
    {
        std::cout << "Error: PhysicsCommon pointer is null." << std::endl;
        return nullptr;
    }
    return physicsCommonPtr;
}

reactphysics3d::PhysicsWorld* PhysicsManager::getPhysicsWorldPtr()
{
    if (physicsWorldPtr == nullptr)
    {
        std::cout << "Error: PhysicsWorld pointer is null." << std::endl;
        return nullptr;
    }
    return physicsWorldPtr;
}

reactphysics3d::PhysicsCommon* PhysicsManager::createPhyisicsCommonPtr()
{
    if (physicsCommonPtr != nullptr) 
    {
		std::cout << "Error: PhysicsCommon pointer already exists." << std::endl;
		return physicsCommonPtr;
    }
    physicsCommonPtr = new reactphysics3d::PhysicsCommon();
    return physicsCommonPtr;
}

reactphysics3d::PhysicsWorld* PhysicsManager::createPhysicsWorldPtr(reactphysics3d::PhysicsCommon* physicsCommonPtr, const reactphysics3d::PhysicsWorld::WorldSettings* settings)
{
    if (physicsWorldPtr != nullptr) 
    {
        std::cout << "Error: PhysicsWorld pointer already exists." << std::endl;
        return physicsWorldPtr;
    }
    if (physicsCommonPtr == nullptr) 
    {
		std::cout << "Error: PhysicsCommon pointer is null. Must create physics common before world." << std::endl;
		return nullptr;
    }

    // Create the physics world with the provided settings
    // Note: settings is a const reference, so modify caller-provided settings if needed before calling

    // create the settings if non was provided.
	reactphysics3d::PhysicsWorld::WorldSettings worldSettings;
    if (settings == nullptr) 
    {
        // Create the world settings
        worldSettings.defaultVelocitySolverNbIterations = velocitySolverNbIterations;
        worldSettings.isSleepingEnabled = false;
        worldSettings.gravity = reactphysics3d::Vector3(0, gravity, 0);
    } 
    else
    {
        // settings is not null so use the provided settings.
        worldSettings = *settings;
    }
    physicsWorldPtr = physicsCommonPtr->createPhysicsWorld(worldSettings);

    return physicsWorldPtr;
}
