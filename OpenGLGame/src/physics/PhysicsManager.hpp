#pragma once
#include <reactphysics3d/reactphysics3d.h>
class PhysicsManager
{
public:
	const float gravity = -9.81f;
	const int velocitySolverNbIterations = 20;
public:
	PhysicsManager() = default;
	~PhysicsManager() = default;
    int test();

	reactphysics3d::PhysicsCommon* getPhysicsCommonPtr();
	reactphysics3d::PhysicsWorld* getPhysicsWorldPtr();

	reactphysics3d::PhysicsCommon* createPhyisicsCommonPtr();
	reactphysics3d::PhysicsWorld* createPhysicsWorldPtr(reactphysics3d::PhysicsCommon* physicsCommonPtr, const reactphysics3d::PhysicsWorld::WorldSettings* settings = nullptr);

private:
	// First you need to create the PhysicsCommon object.
	// This is a factory module that you can use to create physics
	// world and other objects. It is also responsible for
	// logging and memory management
	reactphysics3d::PhysicsCommon* physicsCommonPtr = nullptr;

	// physics world
	reactphysics3d::PhysicsWorld* physicsWorldPtr = nullptr;

};

