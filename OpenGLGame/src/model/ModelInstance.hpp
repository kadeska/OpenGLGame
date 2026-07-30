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
        Model* model;
        reactphysics3d::RigidBody* rigidBody;
        rp3d::PhysicsWorld* physicsWorldptr;
        glm::vec3 position;
        glm::vec3 scale;
        //MyRigidBody* rigidBody = nullptr;
        ModelInstance(const char* modelName, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f), rp3d::PhysicsWorld* physicsWorldptr = nullptr)
            : position(pos), scale(scl), physicsWorldptr(physicsWorldptr)
        {
            ModelFactory modelFactory;
            //model = new Model(path); // path is given from Scene::populateScene()


			// create a model object using our model factory, and set its position to the given position
			model = modelFactory.createModel(modelName);
            
            // check if the model was created succesfully.
            if (!model) {
                //std::cerr << "Error: Failed to create model: " << modelName << std::endl;
                log("Error: Failed to create model: " + std::string(modelName), LogType::ERROR);    

                return;
            }
            model->loadSuccessful = true;

            // set the models position. 
            // 
            // If the model is flagged to have a rigid body then create a rigid body.
            // 
            // TODO: Implement a bool flag (hasRigidBody) in the ModelInstance struct, 
            // this can be used for checking if this model should expect to have a rigid body attached to it.
            // If the flag is set to true and there is no rigidbody attached, throw a soft error and proceed with rendering as usual. 
            // 
            model->setPosition(position);
            
            // create rigidbody at position and add it to the physics world
			rigidBody = physicsWorldptr->createRigidBody(reactphysics3d::Transform(reactphysics3d::Vector3(position.x, position.y, position.z), reactphysics3d::Quaternion::identity()));
			rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);

			//rigidBody = new MyRigidBody(rp3d::Vector3(position.x, position.y, position.z), physicsWorldptr, model->getPtrIndex());
        }

        void update() 
        {
			// update the models position based on the rigid bodys position in the physics world.
            reactphysics3d::Vector3 pos = rigidBody->getTransform().getPosition();
            model->setPosition(glm::vec3(pos.x, pos.y, pos.z));
        }

        ~ModelInstance()
        {
            if (model) delete model;
        }
    };

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