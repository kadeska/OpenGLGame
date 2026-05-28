#include "Scene.hpp"
#include "../utils/FileManager.hpp"

#include "../physics/PhysicsWorld.hpp"
//#include "../physics/RigidBody.hpp"

PhysicsWorld* physicsWorld = nullptr;

Scene::Scene()
{
	std::cout << "[Scene()] Creating scene..." << std::endl;

	//FileManager::fileExists("path");
	//FileManager::saveToFile("filename", "data");

	// create physics world, then create some model instances and add them to the scene, and add the modelInstances rigid bodys to the physics world..
	physicsWorld = new PhysicsWorld();

	populateScene();
}

Scene::~Scene()
{
	std::cout << "[~Scene()] Destroying scene..." << std::endl;
}

void Scene::populateScene()
{

	std::cout << "[populateScene()] Populating scene..." << std::endl;

	if (physicsWorld == nullptr) 
	{
		std::cout << "ERROR: physics world is null" << std::endl;
		return;
	}

	models.push_back(new ModelInstance::ModelInstance("backpack", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), physicsWorld->getWorld()));
	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(8.0f, 0.0f, 0.0f), glm::vec3(1.0f)));

	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f)));
	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f)));

	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(4.0f, 5.0f, 0.0f), glm::vec3(1.0f)));
	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(4.0f, 10.0f, 0.0f), glm::vec3(1.0f)));

	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(8.0f, 5.0f, 0.0f), glm::vec3(1.0f)));
	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(8.0f, 10.0f, 0.0f), glm::vec3(1.0f)));


	//physicsWorld->getWorld()->


}

// physics sim 

void Scene::updatePhysicsWorld(const double timestep)
{
	if (physicsWorld == nullptr) 
	{
		std::cout << "ERROR : physics world is nullptr" << std::endl;
		return;
	}

	physicsWorld->getWorld()->update(timestep);
}
