#include "PhysicsManager.hpp"
#include <reactphysics3d/reactphysics3d.h>
#include <iostream>

//#include "PhysicsRigidBody.hpp"
#include <reactphysics3d/mathematics/Transform.h>

#include "../utils/Logger.hpp"
using namespace logger;

const int nbIterationsVelocitySolver = 15;
const int nbIterationsPositionSolver = 8;

rp3d::PhysicsCommon physicsCommon;

PhysicsManager::PhysicsManager()
{
}

rp3d::PhysicsWorld* PhysicsManager::createPhysicsWorld()
{
	// Create the world settings
	rp3d::PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 20;
	settings.isSleepingEnabled = false;
	settings.gravity = rp3d::Vector3(0, -9.81, 0);

	rp3d::PhysicsWorld* world = physicsCommon.createPhysicsWorld(settings);

	// Change the number of iterations of the velocity solver
	world->setNbIterationsVelocitySolver(nbIterationsVelocitySolver);

	// Change the number of iterations of the position solver
	world->setNbIterationsPositionSolver(nbIterationsPositionSolver);

	// Disable the sleeping technique
	world->enableSleeping(false);

	return world;
}

void PhysicsManager::updatePhysicsWorld(const double timestep, rp3d::PhysicsWorld* world)
{
	world->update(timestep);
	// 
	
}
