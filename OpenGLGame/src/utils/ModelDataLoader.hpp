#pragma once
#include <filesystem>
#include <iostream>

// this will be respocible for loading the model data from the custom files, and if the files dont exist then it will generate the data from the model and save it to custom files. 
// This is to speed up loading times for models, since loading the model data from the custom files is much faster than loading the model data from the model file and processing it with assimp every time.
namespace ModelDataLoader
{
	// loads all the models data from the given path.
	// If the data files can not be found at the given path, then it will generate the data from the model and save it to custom files in the default model data directory.
	bool loadModels(std::filesystem::path _path);
}