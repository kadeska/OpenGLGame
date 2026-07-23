#include "Scene.hpp"
#include "../utils/FileManager.hpp"

#include "../physics/PhysicsManager.hpp"

#include "../model/ModelFactory.hpp"

//#include "../physics/PhysicsWorld.hpp"
//#include "../physics/RigidBody.hpp"

//PhysicsWorld* physicsWorld = nullptr;

PhysicsManager* physicsManager;

Scene::Scene()
{
	std::cout << "[Scene()] Creating scene..." << std::endl;

	physicsManager = new PhysicsManager();

	//FileManager::fileExists("path");
	//FileManager::saveToFile("filename", "data");

	// create physics world, then create some model instances and add them to the scene, and add the modelInstances rigid bodys to the physics world..
	physicsManager->createPhyisicsCommonPtr();
	physicsManager->createPhysicsWorldPtr(physicsManager->getPhysicsCommonPtr());


	populateScene();
}

Scene::~Scene()
{
	std::cout << "[~Scene()] Destroying scene..." << std::endl;
}

void Scene::populateScene()
{

	std::cout << "[populateScene()] Populating scene..." << std::endl;

	if (physicsManager == nullptr) 
	{
		std::cout << "ERROR: physics world is null" << std::endl;
		return;
	}

	// create a floor
	rp3d::Vector3 floorPosition(0.0f, -5.0f, 0.0f);
	rp3d::Quaternion floorOrientation = rp3d::Quaternion::identity();
	rp3d::Transform floorTransform(floorPosition, floorOrientation);

	// Create a box shape for the floor (width, height, depth)
	rp3d::Vector3 extent(20.0f, 1.0f, 20.0f);
	rp3d::PhysicsCommon physicsCommon;
	rp3d::BoxShape* floorShape = physicsCommon.createBoxShape(extent);

	// Create the rigid body for the floor
	rp3d::RigidBody* floorBody = physicsManager->getPhysicsWorldPtr()->createRigidBody(floorTransform);

	// Add the collider to the rigid body
	rp3d::Collider* floorCollider = floorBody->addCollider(floorShape, rp3d::Transform::identity());

	// Set the rigid body to be static
	floorBody->setType(rp3d::BodyType::STATIC);


	models.push_back(new ModelInstance::ModelInstance("backpack", glm::vec3(0.0f, -4.0f, 0.0f), glm::vec3(1.0f), physicsManager->getPhysicsWorldPtr()));
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
	if (physicsManager == nullptr) 
	{
		std::cout << "ERROR : physics manager is nullptr" << std::endl;
		return;
	}

	//physicsManager->getPhysicsWorldPtr()->update(timestep);
	physicsManager->updatePhysicsWorld(timestep);

	for (int i = 0; i < models.size(); i++)
	{
		ModelInstance::ModelInstance* modelInstance = models[i];
		if (modelInstance != nullptr && modelInstance->rigidBody != nullptr)
		{
			//rp3d::Transform transform = modelInstance->rigidBody->getTransform();
			//rp3d::Vector3 position = transform.getPosition();
			//modelInstance->position = glm::vec3(position.x, position.y, position.z);
			// Get the updated position of the body
	        const reactphysics3d::Transform& transform = modelInstance->rigidBody->getTransform();
	        const reactphysics3d::Vector3& position = transform.getPosition();
			modelInstance->model->setPosition(glm::vec3(position.x, position.y, position.z));
		}
	}

	//physicsManager->populateArrayOfRigidBodies(physicsManager->getArrayOfRigidBodies());
}
