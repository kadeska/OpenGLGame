#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <stb_image/stb_image.h>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>

#include "mesh/mesh.hpp"

#include "../utils/Logger.hpp"
using namespace logger;


// the necessary data needed to render
struct ModelData
{
    std::vector<Texture> textures_loaded = std::vector<Texture>(100);
    std::vector<Mesh> meshes = std::vector<Mesh>(1000);
    std::string modelName = "null";
};


class Model
{
private:
	// This is the index of this model pointer in the model factorys loaded models vector. 
    // This is used to easily remove this model from the loaded models vector when this model is destroyed, 
    // and to check if this model is already loaded in the model factory when creating a new model.
    int ptrIndex = -1; 
public:
	bool loadSuccessful = false;

    // model data 
    //std::vector<Texture> textures_loaded; // all the loaded textures for this model	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    //std::vector<Mesh>    meshes; // all the meshes that make up this model
	std::string directory; // the directory path
	std::string modelName; // the model name (filename without extension)
    bool gammaCorrection = false;

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	//bool loadSuccessful;

    ModelData modelData;

    // constructor, expects a filepath to a 3D model.
    Model(ModelData _modelData)
    {
        if (modelData.meshes.empty()) 
        {
            //std::cout << "ERROR::MODEL:: No meshes provided in model data." << std::endl;
            log("No meshes provided in model data.", LogType::ERROR);
            //loadModel(modelData.modelName);
        }
        else
        {
            //std::cout << "INFO::MODEL:: Meshes provided in model data, loading model data from provided data..." << std::endl;
            log("Meshes found in ModelData object, loading model data...");
            this->modelData.meshes = _modelData.meshes;
            this->modelData.textures_loaded = _modelData.textures_loaded;
			this->modelData.modelName = _modelData.modelName;
			this->modelName = _modelData.modelName;
            log("Done loading model data from ModelData object.");
        }
    }


    // draws the model, and thus all its meshes
    void Draw(Shader* shader)
    {
        if (loadSuccessful) 
        {
            for (unsigned int i = 0; i < this->modelData.meshes.size(); i++)
                this->modelData.meshes[i].Draw(shader);
        }
        
    }

    void setPtrIndex(int index)
    {
        // Only allow setting the ptr index when it hasent been set before, 
        // and only if the model has been succesfully loaded.
        if ((ptrIndex == -1) && loadSuccessful) 
        {
            this->ptrIndex = index;
        }
        
	}

    int getPtrIndex()
    {
        return ptrIndex;
	}

	void setPosition(glm::vec3 pos)
	{
        if (loadSuccessful) 
        {
            this->position = pos;
        }
	}

    std::string getName()
    {
		return modelName;
    }
};


