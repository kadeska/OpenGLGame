#pragma once
#include <glm/glm.hpp> 


#include "model.hpp"
#include "../utils/FileManager.hpp"
#include "modelfactory.hpp"

//#include "../physics/RigidBody.hpp"
//#include <reactphysics3d/engine/PhysicsWorld.h>

#include <reactphysics3d/reactphysics3d.h>       

#include "../utils/Logger.hpp"
using namespace logger;


namespace ModelInstance
{
    

    // ModelInstance structure to hold model data, RigidBody if applicable, and transformation information
    struct ModelInstance
    {
        ModelFactory modelFactory;

        Model* model;
        reactphysics3d::RigidBody* rigidBody;
        reactphysics3d::SphereShape* sphereShape;
		reactphysics3d::BoxShape* boxShape;
        reactphysics3d::Collider* collider;
        rp3d::PhysicsWorld* physicsWorldptr;
        glm::vec3 position;
        glm::vec3 scale;
        float colliderSphereRadius = 1.0f;
        bool isDynamic = false;
        rp3d::Transform prevRigidBodyTransform = rp3d::Transform::identity();
        //MyRigidBody* rigidBody = nullptr;
        ModelInstance(const char* modelName, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f), rp3d::PhysicsWorld* physicsWorldptr = nullptr, bool isDynamic = false)
            : position(pos), scale(scl), physicsWorldptr(physicsWorldptr), isDynamic(isDynamic)
        {
            
            //model = new Model(path); // path is given from Scene::populateScene()


			// create a model object using our model factory, and set its position to the given position
			model = modelFactory.createModel(modelName);
            
            // check if the model was created succesfully.
            if (!model) {
                //std::cerr << "Error: Failed to create model: " << modelName << std::endl;
                log("Error: Failed to create model: " + std::string(modelName), LogType::ERROR);    

                return;
            }
            // Set load successful first before trying to set its position. 
            model->loadSuccessful = true;
            model->setPosition(position);
            
            
        }

        // I do this update already in physics manager
   //     void update() 
   //     {
			//// update the models position based on the rigid bodys position in the physics world.
   //         reactphysics3d::Vector3 pos = rigidBody->getTransform().getPosition();
   //         model->setPosition(glm::vec3(pos.x, pos.y, pos.z));
   //     }

		std::string getModelName()
		{
			if (model)
			{
				return model->getName();
			}
			else
			{
				return "null";
			}
		}

        ~ModelInstance()
        {
            if (model) delete model;
        }

    };

    // get the transform of the given model instance
    glm::vec3 getTransform(const ModelInstance modelInstance);


    //int readDataFromFile(const std::string& _filename, std::string& _outData)
    //{
    //    std::cout << "Reading data from file: " << _filename;
    //    std::string content;
    //    std::string line;
    //    int lineCount = 0;
    //    std::ifstream MyReadFile(_filename);
    //    if (!MyReadFile)
    //    {
    //        std::cout << "Failed to open file: " << _filename;
    //        return -1; // indicate failure to open file
    //    }
    //    while (getline(MyReadFile, line)) {
    //        content.append(line + '\n');
    //        lineCount++;
    //    }
    //    MyReadFile.close();
    //    _outData = content;
    //    if (content.empty()) { return 1; }
    //    return 0;
    //}
}


inline glm::vec3 ModelInstance::getTransform(const ModelInstance modelInstance) {
    return modelInstance.position;
}   