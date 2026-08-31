#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include "../model/ModelInstance.hpp"

// PhysicsManager class is responsible for all things physics. 
// This class is the main interface for my games physics system.
class PhysicsManager
{
public:
	const float gravity = -0.55f;
	const int velocitySolverNbIterations = 20;
public:
	PhysicsManager();
	~PhysicsManager() = default;
    int test();

	void updatePhysicsWorld(const double timestep, const float factor);

	reactphysics3d::PhysicsCommon* getPhysicsCommonPtr();
	reactphysics3d::PhysicsWorld* getPhysicsWorldPtr();

	reactphysics3d::PhysicsCommon* createPhyisicsCommonPtr();
	reactphysics3d::PhysicsWorld* createPhysicsWorldPtr(reactphysics3d::PhysicsCommon* physicsCommonPtr, const reactphysics3d::PhysicsWorld::WorldSettings* settings = nullptr);

	void populateArrayOfRigidBodies(std::vector<reactphysics3d::RigidBody*>& rigidBodies);
	void createRigidBodyForModelInstance(ModelInstance::ModelInstance* modelInstance);
	
	std::vector<reactphysics3d::RigidBody*>& getArrayOfRigidBodies();
	std::vector<ModelInstance::ModelInstance*>& getArrayOfModelInstances();

	void addModelInstance(ModelInstance::ModelInstance* modelInstance);

	void makeFloor(ModelInstance::ModelInstance* modelInstance);

private:
	// First you need to create the PhysicsCommon object.
	// This is a factory module that you can use to create physics
	// world and other objects. It is also responsible for
	// logging and memory management
	reactphysics3d::PhysicsCommon* physicsCommonPtr = nullptr;

	// physics world
	reactphysics3d::PhysicsWorld* physicsWorldPtr = nullptr;

	// Array of rigid bodies in the physics world
	std::vector<reactphysics3d::RigidBody*> rigidBodies = {};

	std::vector<ModelInstance::ModelInstance*> modelInstances = {};
};

