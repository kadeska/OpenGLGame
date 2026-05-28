#pragma once
#include <filesystem>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>

#include "../model/mesh/mesh.hpp"

// this will be respocible for loading the model data from the custom files, and if the files dont exist then it will generate the data from the model and save it to custom files. 
// This is to speed up loading times for models, since loading the model data from the custom files is much faster than loading the model data from the model file and processing it with assimp every time.
namespace ModelDataLoader
{
#define MAX_BONE_INFLUENCE 4

	struct Vertex {
		// position
		glm::vec3 Position;
		// normal
		glm::vec3 Normal;
		// texCoords
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
		//bone indexes which will influence this vertex
		int m_BoneIDs[MAX_BONE_INFLUENCE];
		//weights from each bone
		float m_Weights[MAX_BONE_INFLUENCE];
	};

	struct Texture {
		unsigned int id;
		std::string type;
		std::string path;
	};
	// the necessary data needed to render
	struct ModelData
	{
		std::vector<Texture> textures_loaded = {};
		std::vector<Mesh> meshes = {};
		std::string modelName = "";
	};


	namespace fs = std::filesystem;

	// loads all the models data from the given path.
	// If the data files can not be found at the given path, then it will generate the data from the model and save it to custom files in the default model data directory.
	bool loadModelData(std::filesystem::path _path_to_data, std::string _modelName) 
	{
		std::filesystem::path modelDataPath = _path_to_data / _modelName;
		// check if path exists. 
		// modelDataPath should be (_path_to_data + _modelName) so then When I call loadModelData()
		// I can give it the path to the data folder, and give it the model name, and it will check if the models 
		// data folder exists at the given path.
		// if it does then load the model data from the files at this path

		if (std::filesystem::exists(modelDataPath)) 
		{
			// load model data files from this path
			std::cout << "Model data folder found for model: " << _modelName << std::endl;
			for (auto const& entry : fs::directory_iterator(modelDataPath)) 
			{
				if (!entry.is_regular_file()) continue;

				std::ifstream file(entry.path());
				if (!file) 
				{
					std::cerr << "Failed to open: " << entry.path() << '\n';
					continue;
				}

				// this is where I need to make a Mesh object from the data in this file, 
				// and add it to the model data struct that will be used to construct the model object.

				std::string line;
				while (std::getline(file, line)) 
				{
					std::string_view v(line);
					//if () {} // parse the data in this line
				}
			}
		}

	}

	bool parseLine(std::string_view s) 
	{
		auto skip_spaces = [&]() {
			while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front()))) s.remove_prefix(1);
			};
		auto expect_char = [&](char ch)->bool {
			skip_spaces();
			if (s.empty() || s.front() != ch) return false;
			s.remove_prefix(1);
			return true;
			};
		auto parse_double = [&](double& out)->bool {
			skip_spaces();
			if (s.empty()) return false;
			const char* begin = s.data();
			std::from_chars_result r = std::from_chars(begin, begin + s.size(), out);
			if (r.ec != std::errc()) return false;
			size_t consumed = r.ptr - begin;
			s.remove_prefix(consumed);
			return true;
			};

		double x, y, z;
		if (!expect_char('X')) return false;
		if (!expect_char(':')) return false;
		if (!parse_double(x)) return false;
		if (!expect_char('Y')) {
			// allow a separating space then 'Y'
			if (!expect_char(' ') || !expect_char('Y')) return false;
		}
		if (!expect_char(':')) return false;
		if (!parse_double(y)) return false;
		if (!expect_char('Z')) {
			if (!expect_char(' ') || !expect_char('Z')) return false;
		}
		if (!expect_char(':')) return false;
		if (!parse_double(z)) return false;
		return true;
	}
}