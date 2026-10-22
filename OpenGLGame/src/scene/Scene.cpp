#include "Scene.hpp"
#include "../utils/FileManager.hpp"

//#include "../physics/PhysicsManager.hpp"

//#include "../model/ModelFactory.hpp"

#include "../utils/Logger.hpp"
#include "../physics/PhysicsManager.hpp"
using namespace logger;

rp3d::PhysicsWorld* physicsWorld = nullptr;

rp3d::RigidBody* floorBody = nullptr;
rp3d::Collider* floorCollider = nullptr;
rp3d::BoxShape* floorShape = nullptr;

Scene::Scene(rp3d::PhysicsWorld* _physicsWorld)
{
	//std::cout << "[Scene()] Creating scene..." << std::endl;
	log("Scene() constructor", LogType::DEBUG);
	log("Creating scene...");
	physicsWorld = _physicsWorld;

	//physicsManager = new PhysicsManager();

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

	if (physicsWorld == nullptr) 
	{
		//std::cout << "ERROR: physics world is null" << std::endl;
		log("Physics world is null", LogType::ERROR);
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
	

	// ---------------------------------------------------------------------------------------------------------------------------------------------------------------
	//
	// Change the way I create a scene. I want to be able to load it from a save file. I want to generate a meta data file that contains the information about the models in the scene,
	// their positions, scales, and other properties. 
	// Then I can load the scene from that meta data file. 
	// This will allow me to easily create and modify scenes without having to hard code them in the source code.
	// 
	// I already have the model data of each model saved in a data folder, I can reuse those model data files to load the models in the scene. 
	// The only things I should be storing in the scene meta data file are the 
	// (model name, ID)(name and ID are for identification), position(in the scene), scale(if different from default found in model data file), and any additional properties. 
	// Maybe have a seperate file for each model that needs a properties list such as an entity like an enemy or chest, or the players stats.
	// Have some sort of tree structure for the save system. 
	// 
	// Game save system should be able to save the game state, including the scene, player stats, inventory, and any other relevant data.
	// 
	// Keep it simple for ease of modding.
	// Store Game Object IDs and positions in the scene meta data file, and have a seperate file for each Game Object that contains its properties.
	// so each line in the meta data file should look something like this:
	//     // ModelName(name of 3D model for model loading), ID(Unique identifier, used like an index), propertiesFileName(contains all other data needed).
	// I hope this structure would allow for easy modding and adding new content to the game.
	// use the model name to load the 3d model into memory and use the ID to index the model in the scene. Use the properties file to load the game object properties such as type, position, health, damage, etc.
	// 
	// 
	// 
	// --------------------------------------------------



	// load save.

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

void Scene::updatePhysicsWorld(const double timestep, PhysicsManager* _physicsManager )
{
	if (_physicsManager == nullptr) 
	{
		//std::cout << "ERROR : physics manager is nullptr" << std::endl;
		log("Physics manager is nullptr", LogType::ERROR);
		return;
	}
	if (getPhysicsWorld() == nullptr) 
	{
		log("Physics world is nullptr", LogType::ERROR);
		return;
	}

	_physicsManager->updatePhysicsWorld(timestep, getPhysicsWorld());
}

void Scene::updateModelsFromPhysicsWorld(rp3d::PhysicsWorld* world, float factor)
{
	for (ModelInstance::ModelInstance* modelInstance : models) 
	{
		int index = modelInstance->model->getPtrIndex();
		rp3d::Transform prevTtransform = modelInstance->prevRigidBodyTransform;
		
		//---------------------- debug

		if (index == -1) {
			log("Invalid model index found.", LogType::ERROR);
			continue;
		}
		log("Number of rigid bodies: " + std::to_string(world->getNbRigidBodies()), LogType::DEBUG);
		if (world->getRigidBody(index) == nullptr) {
			log("Invalid rigid body found for model index: " + std::to_string(index), LogType::ERROR);
			continue;
		}
		//-----------------------------------


		// This line crashes becausbe there are no rigid bodies in the world.
		rp3d::Transform currTransform = world->getRigidBody(index)->getTransform(); // CRASH :: Index is -1 // CRASH :: Index is 0 ?? is the rigidbody valid?

		rp3d::Transform interpolatedTransform = rp3d::Transform::interpolateTransforms(prevTtransform, currTransform, factor);

		modelInstance->position = world->getRigidBody(index)->getTransform().getPosition();
	}
}
