#pragma once
#include "model.hpp"
#include <filesystem>
#include "MeshData.hpp"

class ModelFactory
{
public:
	ModelFactory() 
	{
		loadedModels = std::vector<Model*>();
	}
private:

	std::vector<Model*> loadedModels;

	//MeshData::MeshData modelData;

	
public:
	std::vector<Model*> getLoadedModels();
	// returns the index of the model pointer in the loaded models vector, or -1 if the pointer in invalid.
	int putLoadedModel(Model* model);
	bool removeLoadedModelPtr(Model* model);
	bool removeLoadedModelByIndex(int index);


	// This is the main function to call when you want to create a model object.
	// will return nullptr if it cant find or generate the given model name
	// otherwise it will return a pointer to the model object that was created
	//
	// createModel function should take a name of the model, and find the model data folder with that name, 
    // and load the mesh data files from that folder to construct the model object.
	//
	Model* createModel(std::string const& modelFolderName, bool gamma = false);

private:

	bool constructModelObjectFromDataFolder(std::string modelFolderName);
	bool constructModelObjectFrom3dFile(std::string filename);
	void populateModelData(std::string filename);

	//void processNode(aiNode* node, const aiScene* scene);

	//Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	
	// loads a model file with assimp into memory
	//void loadModelFile(std::string const& path);

	// This is the main loading function that is called by the createModel function. It will first try to load the model data from a data file, if that fails it will try to load the model from the 3d file.
	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(std::string const& path);

	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);

	// --- parseModelDataFolder: build one MeshData per file, initialize locals, and return results ---
	std::vector<MeshData::MeshData> parseModelDataFolder(std::string folderName);
	std::optional<std::tuple<float, float, float>> parse_xyz_fast(std::string_view s);


};

