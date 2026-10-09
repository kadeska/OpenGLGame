#include "Scene.hpp"
#include "../utils/FileManager.hpp"

#include "../physics/PhysicsManager.hpp"

#include "../model/ModelFactory.hpp"

#include "../utils/Logger.hpp"
using namespace logger;

PhysicsManager* physicsManager;

rp3d::RigidBody* floorBody = nullptr;
rp3d::Collider* floorCollider = nullptr;
rp3d::BoxShape* floorShape = nullptr;

Scene::Scene()
{
	//std::cout << "[Scene()] Creating scene..." << std::endl;
	log("Scene() constructor", LogType::DEBUG);
	log("Creating scene...");

	physicsManager = new PhysicsManager();

	//FileManager::fileExists("path");
	//FileManager::saveToFile("filename", "data");

	// create physics world, then create some model instances and add them to the scene, and add the modelInstances rigid bodys to the physics world..
	//physicsManager->createPhyisicsCommonPtr();
	//physicsManager->createPhysicsWorldPtr(physicsManager->getPhysicsCommonPtr());


	populateScene();
}

Scene::~Scene()
{
	//std::cout << "[~Scene()] Destroying scene..." << std::endl;
	log("Destroying scene...");
}



void Scene::populateScene()
{

	//std::cout << "[populateScene()] Populating scene..." << std::endl;
	log("Populating scene...");

	if (physicsManager == nullptr) 
	{
		//std::cout << "ERROR: physics world is null" << std::endl;
		log("Physics manager is null", LogType::ERROR);
		return;
	}

	// create a floor
	//rp3d::Vector3 floorPosition(0.0f, -30.0f, 0.0f);
	//rp3d::Quaternion floorOrientation = rp3d::Quaternion::identity();
	//rp3d::Transform floorTransform(floorPosition, floorOrientation);

	//// Create a box shape for the floor (width, height, depth)
	//rp3d::Vector3 extent(500.0f, 1.0f, 500.0f);
	//rp3d::PhysicsCommon physicsCommon;
	//floorShape = physicsCommon.createBoxShape(extent);

	//// Create the rigid body for the floor
	//floorBody = physicsManager->getPhysicsWorldPtr()->createRigidBody(floorTransform);

	//// Add the collider to the rigid body
	//floorCollider = floorBody->addCollider(floorShape, rp3d::Transform::identity());

	//// Set the rigid body to be static
	//floorBody->setType(rp3d::BodyType::STATIC);


	// 
	//models.push_back(new ModelInstance::ModelInstance("backpack", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), physicsManager->getPhysicsWorldPtr()));
	
	models.push_back(new ModelInstance::ModelInstance("cat", rp3d::Vector3(1.0f, 10.0f, 1.0f), glm::vec3(0.05f), /*physicsManager->getPhysicsWorldPtr(),*/ true));
	//models.push_back(new ModelInstance::ModelInstance("cat", glm::vec3(2.0f, 20.0f, 2.0f), glm::vec3(0.05f), physicsManager->getPhysicsWorldPtr(), true));
	//models.push_back(new ModelInstance::ModelInstance("cat", glm::vec3(3.0f, 30.0f, 3.0f), glm::vec3(0.05f), physicsManager->getPhysicsWorldPtr(), true));
	//models.push_back(new ModelInstance::ModelInstance("cat", glm::vec3(4.0f, 40.0f, 4.0f), glm::vec3(0.05f), physicsManager->getPhysicsWorldPtr(), true));
	//models.push_back(new ModelInstance::ModelInstance("cat", glm::vec3(5.0f, 50.0f, 5.0f), glm::vec3(0.05f), physicsManager->getPhysicsWorldPtr(), true));
	//models.push_back(new ModelInstance::ModelInstance("cat", glm::vec3(6.0f, 60.0f, 6.0f), glm::vec3(0.05f), physicsManager->getPhysicsWorldPtr(), true));
	//models.push_back(new ModelInstance::ModelInstance("cat", glm::vec3(7.0f, 70.0f, 7.0f), glm::vec3(0.05f), physicsManager->getPhysicsWorldPtr(), true));
	//models.push_back(new ModelInstance::ModelInstance("cat", glm::vec3(8.0f, 80.0f, 8.0f), glm::vec3(0.05f), physicsManager->getPhysicsWorldPtr(), true));
	//models.push_back(new ModelInstance::ModelInstance("cat", glm::vec3(9.0f, 90.0f, 9.0f), glm::vec3(0.05f), physicsManager->getPhysicsWorldPtr(), true));
	
	
	models.push_back(new ModelInstance::ModelInstance("floor", rp3d::Vector3(100.0f, 1.0f, 100.0f), glm::vec3(1.0f), /*physicsManager->getPhysicsWorldPtr(),*/ false));

	
	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(8.0f, 0.0f, 0.0f), glm::vec3(1.0f)));

	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(1.0f)));
	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f)));

	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(4.0f, 5.0f, 0.0f), glm::vec3(1.0f)));
	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(4.0f, 10.0f, 0.0f), glm::vec3(1.0f)));

	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(8.0f, 5.0f, 0.0f), glm::vec3(1.0f)));
	//models.push_back(new ModelInstance::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(8.0f, 10.0f, 0.0f), glm::vec3(1.0f)));

	//physicsWorld->getWorld()->


	// after the models are loaded create the rigid bodies for each model.

	//for (int i = 0; i < models.size(); i++)
	//{
	//	ModelInstance::ModelInstance* modelInstance = models[i];
	//	if (modelInstance != nullptr)
	//	{
	//		physicsManager->createRigidBodyForModelInstance(modelInstance);
	//		physicsManager->addModelInstance(modelInstance);

	//		if (modelInstance->getModelName() == "floor") 
	//		{
	//			physicsManager->makeFloor(modelInstance);
	//		}
	//	}
	//}

	log("Done populating scene.");

}

// physics sim 

void Scene::updatePhysicsWorld(const double timestep, rp3d::PhysicsWorld* world)
{
	if (physicsManager == nullptr) 
	{
		//std::cout << "ERROR : physics manager is nullptr" << std::endl;
		log("Physics manager is nullptr", LogType::ERROR);
		return;
	}

	physicsManager->updatePhysicsWorld(timestep, world);
}

void Scene::updateModelsFromPhysicsWorld(rp3d::PhysicsWorld* world, float factor)
{
	for (ModelInstance::ModelInstance* modelInstance : models) 
	{
		int index = modelInstance->model->getPtrIndex();
		rp3d::Transform prevTtransform = modelInstance->prevRigidBodyTransform;
		rp3d::Transform currTransform = world->getRigidBody(index)->getTransform();

		rp3d::Transform interpolatedTransform = rp3d::Transform::interpolateTransforms(prevTtransform, currTransform, factor);

		modelInstance->position = world->getRigidBody(index)->getTransform().getPosition();
	}
}
