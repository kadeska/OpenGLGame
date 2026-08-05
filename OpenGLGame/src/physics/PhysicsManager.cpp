#include "PhysicsManager.hpp"
#include <reactphysics3d/reactphysics3d.h>
#include <iostream>

//#include "PhysicsRigidBody.hpp"
#include <reactphysics3d/mathematics/Transform.h>

#include "../utils/Logger.hpp"
using namespace logger;

PhysicsManager::PhysicsManager()
{
    //std::cout << "PhysiscManager constructor" << std::endl;
    log("PhysicsManager() constructor", LogType::DEBUG);
    createPhyisicsCommonPtr();
	createPhysicsWorldPtr(getPhysicsCommonPtr());
}


void PhysicsManager::updatePhysicsWorld(const double timestep, const float factor)
{
	if (physicsWorldPtr != nullptr)
	{
		// physics world update call
		physicsWorldPtr->update(timestep);
		// update model instance positions based on the physics simulation results.

		for (ModelInstance::ModelInstance* modInst : modelInstances)
		{
			// Null check for rigid body
			if (modInst->rigidBody == nullptr)
			{
				log("ModelInstance has no rigid body. Skipping update for this instance.", LogType::WARNING);
                return;
			}

            if (modInst->rigidBody->getType() == rp3d::BodyType::STATIC) 
            {
				return; // Skip static bodies as they don't move
            }

			// Get the current transform of the rigid body after the physics simulation step
			rp3d::Transform currRigidBodyTransform = modInst->rigidBody->getTransform();

			// Compute the interpolated transform between the previous physics frame and the current physics frame
			// factor represents how far through the current accumulator we are (0 to 1)
			// When factor is 1.0, we just completed a physics step, so use the current transform
			// When factor is 0.0-1.0, we're between physics frames, so interpolate
			rp3d::Transform interpolatedTransform;
			if (factor >= 1.0f)
			{
				// We just completed a physics step, use the current transform
				interpolatedTransform = currRigidBodyTransform;
			}
			else
			{
				// Interpolate between previous and current transforms
				interpolatedTransform = rp3d::Transform::interpolateTransforms(modInst->prevRigidBodyTransform, currRigidBodyTransform, factor);
			}

			// Update the model instance position with the interpolated transform for rendering
			rp3d::Vector3 interpolatedPos = interpolatedTransform.getPosition();
			modInst->position = glm::vec3(interpolatedPos.x, interpolatedPos.y, interpolatedPos.z);

			// Store the current transform as the previous for the next frame
			modInst->prevRigidBodyTransform = currRigidBodyTransform;

			// Display the position of the body
			//std::cout << "Body Position: (" << modInst->position.x << ", " << modInst->position.y << ", " << modInst->position.z << ")" << std::endl;
		}

	}
}

//
// 
// 
//---------------------------------
// TODO: create a logging system (in-progress)
// TODO: Collition
//---------------------------------

reactphysics3d::PhysicsCommon* PhysicsManager::getPhysicsCommonPtr()
{
    if (physicsCommonPtr == nullptr)
    {
        //std::cout << "Error: PhysicsCommon pointer is null." << std::endl;
        log("PhysicsCommon pointer is null", LogType::ERROR);
        return nullptr;
    }
    return physicsCommonPtr;
}

reactphysics3d::PhysicsWorld* PhysicsManager::getPhysicsWorldPtr()
{
    if (physicsWorldPtr == nullptr)
    {
        //std::cout << "Error: PhysicsWorld pointer is null." << std::endl;
        log("PhysicsWorld pointer is null", LogType::ERROR);
        return nullptr;
    }
    return physicsWorldPtr;
}

reactphysics3d::PhysicsCommon* PhysicsManager::createPhyisicsCommonPtr()
{
    if (physicsCommonPtr != nullptr) 
    {
		//std::cout << "Error: PhysicsCommon pointer already exists." << std::endl;
		log("PhysicsCommon pointer already exists", LogType::ERROR);
		return physicsCommonPtr;
    }
    physicsCommonPtr = new reactphysics3d::PhysicsCommon();
    return physicsCommonPtr;
}

reactphysics3d::PhysicsWorld* PhysicsManager::createPhysicsWorldPtr(reactphysics3d::PhysicsCommon* physicsCommonPtr, const reactphysics3d::PhysicsWorld::WorldSettings* settings)
{
    if (physicsCommonPtr == nullptr)
    {
        //std::cout << "Error: PhysicsCommon pointer is null. Must create physics common before world." << std::endl;
        log("PhysicsCommon pointer is null. Must create physics common before world.", LogType::ERROR);
        return nullptr;
    }
    if (physicsWorldPtr != nullptr) 
    {
        //std::cout << "Error: PhysicsWorld pointer already exists." << std::endl;
        log("PhysicsWorld pointer already exists.", LogType::ERROR);
        return physicsWorldPtr;
    }
    

    // Create the physics world with the provided settings
    // Note: settings is a const reference, so modify caller-provided settings if needed before calling

    // create the settings if non was provided.
	reactphysics3d::PhysicsWorld::WorldSettings worldSettings;
    if (settings == nullptr) 
    {
        // Create the world settings
        worldSettings.defaultVelocitySolverNbIterations = velocitySolverNbIterations;
        worldSettings.isSleepingEnabled = false;
        worldSettings.gravity = reactphysics3d::Vector3(0, gravity, 0);
    } 
    else
    {
        // settings is not null so use the provided settings.
        worldSettings = *settings;
    }
    physicsWorldPtr = physicsCommonPtr->createPhysicsWorld(worldSettings);

    return physicsWorldPtr;
}

void PhysicsManager::populateArrayOfRigidBodies(std::vector<reactphysics3d::RigidBody*>& rigidBodies)
{
    if (physicsWorldPtr != nullptr)
    {
        // Implementation for getting array of rigid bodies


        for (int i = 0; i < getPhysicsWorldPtr()->getNbRigidBodies(); i++) 
        {
			rigidBodies.push_back(getPhysicsWorldPtr()->getRigidBody(i));
			//std::cout << "RigidBody " << i << " added to array." << std::endl;
            log("RigidBody " + std::to_string(i) + " added to array.", LogType::DEBUG);
        }
    }
}

void PhysicsManager::createRigidBodyForModelInstance(ModelInstance::ModelInstance* modelInstance)
{
	log("Creating rigid body for model: " + modelInstance->getModelName());
	modelInstance->rigidBody = physicsWorldPtr->createRigidBody(reactphysics3d::Transform(reactphysics3d::Vector3(modelInstance->position.x, modelInstance->position.y, modelInstance->position.z), reactphysics3d::Quaternion::identity()));

	if (modelInstance->isDynamic)
	{
		modelInstance->rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
	}
	else
	{
		modelInstance->rigidBody->setType(reactphysics3d::BodyType::STATIC);
		modelInstance->rigidBody->enableGravity(false);
	}


	modelInstance->sphereShape = physicsCommonPtr->createSphereShape(modelInstance->colliderSphereRadius);
	reactphysics3d::Transform colliderTransform = reactphysics3d::Transform::identity();
	modelInstance->collider = modelInstance->rigidBody->addCollider(modelInstance->sphereShape, colliderTransform);
}

std::vector<reactphysics3d::RigidBody*>& PhysicsManager::getArrayOfRigidBodies()
{
    return rigidBodies;
}

std::vector<ModelInstance::ModelInstance*>& PhysicsManager::getArrayOfModelInstances()
{
    return modelInstances;
}

void PhysicsManager::addModelInstance(ModelInstance::ModelInstance* modelInstance)
{
    modelInstances.push_back(modelInstance);
}

void PhysicsManager::makeFloor(ModelInstance::ModelInstance* modelInstance)
{
	modelInstance->boxShape = physicsCommonPtr->createBoxShape(rp3d::Vector3(500, 1, 500));
	modelInstance->collider = modelInstance->rigidBody->addCollider(modelInstance->boxShape, rp3d::Transform::identity());
	
    
    modelInstance->rigidBody->setType(rp3d::BodyType::STATIC);
	modelInstance->rigidBody->enableGravity(false);

	modelInstance->rigidBody->setTransform(rp3d::Transform(rp3d::Vector3(modelInstance->position.x, modelInstance->position.y, modelInstance->position.z), rp3d::Quaternion::identity()));
}
