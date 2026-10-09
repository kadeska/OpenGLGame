#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include "../model/ModelInstance.hpp"

#include "../scene/Scene.hpp"

#include  "../utils/Logger.hpp"

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
    
	rp3d::PhysicsWorld* createPhysicsWorld();

	void updatePhysicsWorld(const double timestep, rp3d::PhysicsWorld* world);

};

