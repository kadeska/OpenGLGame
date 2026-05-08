#pragma once

#include <iostream>
#include <vector>
#include "../model/ModelInstance.hpp"

class Scene
{
private:
	// this array is basically our "scene"
	std::vector<ModelInstance::ModelInstance*> models;

public:
	Scene();
	~Scene();
	std::vector<ModelInstance::ModelInstance*>& getModels() { return models; }

	void populateScene();
	// this is where the physics simulation step would go, and then we would update the models positions based on the physics simulation results.
	void update(const double dt);
};

