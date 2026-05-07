#pragma once
#include <glm/glm.hpp> 


#include "model.hpp"
#include "../utils/FileManager.hpp"

#include "../physics/RigidBody.hpp"
#include <reactphysics3d/engine/PhysicsWorld.h>

namespace ModelInstance
{
    // ModelInstance structure to hold model data and transformation information
    struct ModelInstance
    {
        Model* model;
        glm::vec3 position;
        glm::vec3 scale;
        RigidBody* rigidBody = nullptr;
        ModelInstance(const char* path, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f), rp3d::PhysicsWorld* physicsWorldptr = nullptr)
            : position(pos), scale(scl)
        {
            //std::string out;
			// do a check here if we have this models data already loaded into a file for faster loading.
    //        if (readDataFromFile("file", out)) 
    //        {
				//std::cout << "Failed to read data from file, loading model from path: " << path << std::endl;
    //        }

			//FileManager::fileExists(path);
            //std::string outdata;
            //FileManager::readDataFromFile("modelData.txt", outdata);

			//std::cout << "Loading model from path: " << path << std::endl;

            model = new Model(path);

			rigidBody = new RigidBody(rp3d::Vector3(position.x, position.y, position.z), physicsWorldptr);
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