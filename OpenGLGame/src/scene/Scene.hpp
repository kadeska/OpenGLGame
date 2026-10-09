#pragma once

#include <iostream>
#include <vector>
#include "../model/ModelInstance.hpp"

class Scene
{
private:
	// FLAGS -----------------------

	// Is this scene a 3d Renderable scene, or is it a 2d UI scene?
	bool isGameScene = true;

	// ------------------------------


	// this array is basically our "scene"
	std::vector<ModelInstance::ModelInstance*> models;

	

public:
	Scene();
	~Scene();
	std::vector<ModelInstance::ModelInstance*>& getModels() { return models; }
	rp3d::PhysicsWorld* physicsWorld = nullptr;

	void populateScene();
	// this is where the physics simulation step would go, and then we would update the models positions based on the physics simulation results.
	//void update(const double dt);

	// physics sim
	void updatePhysicsWorld(const double timestep, rp3d::PhysicsWorld* world);
	void updateModelsFromPhysicsWorld(rp3d::PhysicsWorld* world, float factor);

	rp3d::PhysicsWorld* getPhysicsWorld() { return physicsWorld; }

	// FLAGS getters -----------------------

	bool getIsGameScene() { return isGameScene; }

	// -------------------------------------------
};

