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

	models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), physicsWorld->getWorld()));
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
//void Scene::update(const double dt)
//{
//	// Update physics simulation once per frame
//	if (physicsWorld) {
//		physicsWorld->update(dt);
//	}
//
//	// Then update model positions based on physics results
//	for (ModelInstance::ModelInstance* modInst : models) 
//	{
//		if (modInst && modInst->rigidBody) {
//			// Get the updated position from the rigid body after physics simulation
//			//const rp3d::Transform& transform = modInst->rigidBody->transform;
//			//const rp3d::Vector3& newPos = transform.getPosition();
//			//modInst->position = glm::vec3(newPos.x, newPos.y, newPos.z);
//			//modInst->rigidBody->move(newPos);
//
//			modInst->position = glm::vec3(modInst->rigidBody->transform.getPosition().x, modInst->rigidBody->transform.getPosition().y, modInst->rigidBody->transform.getPosition().z);
//
//			std::cout << "Updated model position to: (" << modInst->position.x << ", " << modInst->position.y << ", " << modInst->position.z << ")" << std::endl;
//		}
//	}
//}

void Scene::updatePhysicsWorld(const double timestep)
{
	if (physicsWorld == nullptr) 
	{
		std::cout << "ERROR : physics world is nullptr" << std::endl;
		return;
	}

	physicsWorld->getWorld()->update(timestep);
}
