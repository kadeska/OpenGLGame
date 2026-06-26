#include "ModelFactory.hpp"

//#include <stb_image/stb_image.h>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
#include <filesystem>

#include "../utils/FileManager.hpp"

#include "../utils/ModelDataLoader.hpp"
#include "mesh/mesh.hpp"


bool testing = false;


// the model pointer
Model* modelPtr = nullptr;

//the model data
ModelData modelData;
//ModelDataLoader::ModelData modelData;

bool loadSuccessful = false;
std::string directory = "";

std::string folderName = "";


typedef std::vector<std::optional<std::tuple<double, double, double>>> MeshResult;




std::vector<Model*> ModelFactory::getLoadedModels()
{
    return loadedModels;
}

int ModelFactory::putLoadedModel(Model* model)
{
	loadedModels.push_back(model);
    return loadedModels.size() - 1;
}

bool ModelFactory::removeLoadedModelPtr(Model* model)
{
    // if the model pointer is nullptr or if the model hasent been loaded yet
    if ((model == nullptr) || model->getPtrIndex() == -1) 
    {
        std::cout << "ERROR::ModelFactory:: Failed to remove model pointer. Invalid model pointer provided, or model hasent been loaded yet." << std::endl;
		return false;
    }
	loadedModels.erase(std::remove(loadedModels.begin(), loadedModels.end(), model), loadedModels.end());
    return true;
}

bool ModelFactory::removeLoadedModelByIndex(int index)
{
    if (index < 0 || index >= loadedModels.size()) 
    {
        std::cout << "ERROR::ModelFactory:: Failed to remove model pointer. Invalid index provided." << std::endl;
		return false;
    }
    loadedModels.erase(loadedModels.begin() + index);
    return true;
}

Model* ModelFactory::createModel(std::string const& modelFolderName, bool gamma)
{
    //FileManager::saveDataToFileAtPath("testing",  + "appData/modelData/" + modelFolderName + "/", "test data");

	folderName = modelFolderName;

    if (constructModelObjectFromDataFolder(modelFolderName))
    {
		// model was successfully constructed from file, return the model
		return modelPtr;
    }
    // model data was not found. Need to load from 3d file
    if (constructModelObjectFrom3dFile(modelFolderName))
    {
        // old function for loading a model from 3d file.
		//loadModel(modelFolderName);
        // model was successfully constructed from 3d file, return the model
        return modelPtr;
    }
	// model data was not found, and failed to load model from 3d file. Return nullptr

	std::cout << "ERROR::ModelFactory:: Failed to construct model object: " << modelFolderName << std::endl;
	std::cout << "Model data file not found, and failed to load model from 3d file. Returning nullptr." << std::endl;
	std::cout << "Please check the file path and ensure the model file exists." << std::endl;
	std::cout << "" << std::endl;
	return nullptr;
}

bool ModelFactory::constructModelObjectFromDataFolder(std::string modelFolderName)
{
    if (FileManager::checkForModelDataFolder(modelFolderName))
    {
        // if this returns true then we have this models data file already
        // lets load the model data from the file instead of loading the model from the model file with assimp, this should be much faster.
        std::cout << "INFO::ModelFactory:: Model data file found. Loading model data from file..." << std::endl;

        // load the model data from the file and construct the model data in memory
        
        populateModelData(modelFolderName);

        modelPtr = new Model(modelData);

        return true; // successfully loaded model data from data file
    }
    return false; // model data file does not exits
}

bool ModelFactory::constructModelObjectFrom3dFile(std::string filename)
{
    return false;
}

void ModelFactory::populateModelData(std::string modelFolderName)
{
    // the mesh data from the loaded folder
    std::vector<MeshData::MeshData> meshData = parseModelDataFolder(modelFolderName);

    Mesh mesh;

    modelData.modelName = modelFolderName;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // We are doing it this way because the top level objects are differant and we cant simply copy the meshData over
    // we need to loop through the data and populate the modelData object with the raw data from the meshData object.
    // The underlying data is the same, but the objects are differant. 

	// TODO: Maybe try to improve this. 

	// Resize modelData.meshes to accommodate all mesh data
	modelData.meshes.resize(meshData.size());

	// Loop through the generated mesh data and populate the modelData object
	// that will be passed to the model constructor.
	for (int meshIndex = 0; meshIndex < meshData.size(); meshIndex++)
	{
		// Populate the vertices, indices, and textures for each mesh

		// Resize the vectors for this mesh to match the incoming data
		modelData.meshes[meshIndex].vertices.resize(meshData[meshIndex].vertices.size());
		modelData.meshes[meshIndex].indices.resize(meshData[meshIndex].indices.size());
		modelData.meshes[meshIndex].textures.resize(meshData[meshIndex].textures.size());

		// vertices
		for (int v = 0; v < meshData[meshIndex].vertices.size(); v++)
		{
			modelData.meshes[meshIndex].vertices[v].Position = meshData[meshIndex].vertices[v].Position;
			modelData.meshes[meshIndex].vertices[v].Normal = meshData[meshIndex].vertices[v].Normal;
			modelData.meshes[meshIndex].vertices[v].TexCoords = meshData[meshIndex].vertices[v].TexCoords;
			modelData.meshes[meshIndex].vertices[v].Tangent = meshData[meshIndex].vertices[v].Tangent;
			modelData.meshes[meshIndex].vertices[v].Bitangent = meshData[meshIndex].vertices[v].Bitangent;

			// Debug first vertex
			if (meshIndex == 0 && v == 0) {
				std::cout << "DEBUG::ModelFactory:: First vertex TexCoords: (" 
						  << modelData.meshes[meshIndex].vertices[v].TexCoords.x << ", "
						  << modelData.meshes[meshIndex].vertices[v].TexCoords.y << ")" << std::endl;
			}

			// Check if any vertex has invalid texture coordinates
			if (meshIndex == 0 && (modelData.meshes[meshIndex].vertices[v].TexCoords.x < 0 || modelData.meshes[meshIndex].vertices[v].TexCoords.x > 1 ||
				modelData.meshes[meshIndex].vertices[v].TexCoords.y < 0 || modelData.meshes[meshIndex].vertices[v].TexCoords.y > 1)) {
				std::cout << "DEBUG::ModelFactory:: Warning - Vertex " << v << " has texture coords outside [0,1]: (" 
						  << modelData.meshes[meshIndex].vertices[v].TexCoords.x << ", "
						  << modelData.meshes[meshIndex].vertices[v].TexCoords.y << ")" << std::endl;
			}
		}

        // Indices
        for (int indicesIndex = 0; indicesIndex < meshData[meshIndex].indices.size(); indicesIndex++) 
        {
			modelData.meshes[meshIndex].indices[indicesIndex] = meshData[meshIndex].indices[indicesIndex];
        }

		// Textures
		for (int t = 0; t < meshData[meshIndex].textures.size(); t++)
		{
			modelData.meshes[meshIndex].textures[t].id = meshData[meshIndex].textures[t].id;
			modelData.meshes[meshIndex].textures[t].path = meshData[meshIndex].textures[t].path;
			modelData.meshes[meshIndex].textures[t].type = meshData[meshIndex].textures[t].type;
		}
	}

	// Load textures for all meshes after model data has been populated
	std::string textureDirectory = FileManager::getDefaultModelDataDir() + "/" + modelFolderName;

	std::cout << "DEBUG::ModelFactory:: Total meshes: " << modelData.meshes.size() << std::endl;
	for (int meshIndex = 0; meshIndex < modelData.meshes.size(); meshIndex++)
	{
		std::cout << "DEBUG::ModelFactory:: Mesh " << meshIndex << " - Vertices: " << modelData.meshes[meshIndex].vertices.size() 
				  << ", Indices: " << modelData.meshes[meshIndex].indices.size() 
				  << ", Textures: " << modelData.meshes[meshIndex].textures.size() << std::endl;

		for (int t = 0; t < modelData.meshes[meshIndex].textures.size(); t++)
		{
			// Check if texture has already been loaded
			bool textureAlreadyLoaded = false;
			for (const auto& loadedTex : modelData.textures_loaded)
			{
				if (loadedTex.path == modelData.meshes[meshIndex].textures[t].path)
				{
					// Texture already loaded, reuse it
					modelData.meshes[meshIndex].textures[t].id = loadedTex.id;
					textureAlreadyLoaded = true;
					break;
				}
			}

			// Load texture if not already loaded
			if (!textureAlreadyLoaded && !modelData.meshes[meshIndex].textures[t].path.empty())
			{
				unsigned int textureID = TextureFromFile(modelData.meshes[meshIndex].textures[t].path.c_str(), textureDirectory, false);
				modelData.meshes[meshIndex].textures[t].id = textureID;

				std::cout << "DEBUG::ModelFactory:: Loaded texture '" << modelData.meshes[meshIndex].textures[t].path 
						  << "' type: " << modelData.meshes[meshIndex].textures[t].type 
						  << " ID: " << textureID << std::endl;

				// Add to loaded textures list for future reference
				modelData.textures_loaded.push_back(modelData.meshes[meshIndex].textures[t]);
			}
		}

		// Setup the mesh VAO/VBO/EBO after all data is populated
		modelData.meshes[meshIndex].setupMeshData();
	}

	std::cout << "INFO::ModelFactory:: Model data populated." << std::endl;
}

void ModelFactory::loadModel(std::string const& path)
{
    if (testing)
    {
        //loadModelFile(path);
    }

    // check if the dir exists
    int result = FileManager::initDefaultModelDataFolder();
    if (!result)
    {
        std::cout << "INFO::FILEMANAGER:: Model data folder already exists. Checking for files..." << std::endl;
        //FileManager::checkForModelDataFiles(path);
        //FileManager::loadDataFile(path);
        //FileManager::checkForModelDataFiles("");
    }
    if (result)
    {
        std::cout << "INFO::FILEMANAGER:: Model data folder does not exist, folder will be created now. \n Loading model data from 3d model files, this may take a while..." << std::endl;
        //loadModelFile(path);
    }
}

//std::vector<Texture> ModelFactory::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
//{
//    std::vector<Texture> textures;
//    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
//    {
//        aiString str;
//        mat->GetTexture(type, i, &str);
//        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
//        bool skip = false;
//        for (unsigned int j = 0; j < modelData.textures_loaded.size(); j++)
//        {
//            if (std::strcmp(modelData.textures_loaded[j].path.data(), str.C_Str()) == 0)
//            {
//                textures.push_back(modelData.textures_loaded[j]);
//                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
//                break;
//            }
//        }
//        if (!skip)
//        {   // if texture hasn't been loaded already, load it
//            Texture texture;
//            texture.id = TextureFromFile(str.C_Str(), directory, false);
//            texture.type = typeName;
//            texture.path = str.C_Str();
//            textures.push_back(texture);
//            modelData.textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
//        }
//    }
//    return textures;
//}

unsigned int ModelFactory::TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

std::vector<MeshData::MeshData> ModelFactory::parseModelDataFolder(std::string folderName)
{
	std::cout << "Parsing model data in folder: " << folderName << std::endl;

	namespace fs = std::filesystem;

	const fs::path folder = FileManager::getDefaultModelDataDir() + "/" + folderName;

	std::vector<MeshData::MeshData> meshResults;

	// this for loop goes through each file in the folder
	for (auto const& entry : fs::directory_iterator(folder)) {
		if (!entry.is_regular_file()) continue;

		std::ifstream in(entry.path());
		if (!in) {
			std::cerr << "Failed to open: " << entry.path() << '\n';
			continue;
		}

		MeshData::MeshData meshData; // one mesh per file
		std::string line;
		int section = 0; // 0 = vertices, 1 = texcoords, 2 = indices, 3 = textures
		size_t tcIndex = 0; // texture coordinate index (per mesh)

		while (std::getline(in, line)) {
			// Check for section separators
			if (line == "::") {
				section++;
				tcIndex = 0; // reset texture coordinate index for next mesh
				continue;
			}

			if (section == 0) {
				// Parse vertices (X:value Y:value Z:value)
				std::string_view v(line);
				if (auto t = parse_xyz_fast(v)) {
					auto [x, y, z] = *t;
					MeshData::MeshData::Vertex vertex{};
					vertex.Position = glm::vec3(x, y, z);
					meshData.vertices.push_back(std::move(vertex));
				}
			}
			else if (section == 1) {
				// Parse texture coordinates (TC:u v)
				if (line.substr(0, 3) == "TC:") {
					try {
						std::string coords = line.substr(3);
						size_t spacePos = coords.find(' ');
						if (spacePos != std::string::npos) {
							float u = std::stof(coords.substr(0, spacePos));
							float v = std::stof(coords.substr(spacePos + 1));

							// Assign texture coordinate to corresponding vertex
							if (tcIndex < meshData.vertices.size()) {
								meshData.vertices[tcIndex].TexCoords = glm::vec2(u, v);
								tcIndex++;
							}
						}
					}
					catch (const std::exception& e) {
						std::cerr << "Failed to parse texture coords: " << line << " Error: " << e.what() << '\n';
					}
				}
			}
			else if (section == 2) {
				// Parse indices (I:value)
				if (line.substr(0, 2) == "I:") {
					try {
						unsigned int index = std::stoul(line.substr(2));
						meshData.indices.push_back(index);
					}
					catch (const std::exception&) {
						std::cerr << "Failed to parse index: " << line << '\n';
					}
				}
			}
			else if (section == 3) {
				// Parse textures (T:type P:path ID:id)
				if (line.substr(0, 2) == "T:") {
					MeshData::MeshData::Texture texture;

					// Parse format: T:type P:path ID:id
					size_t pPos = line.find(" P:");
					size_t idPos = line.find(" ID:");

					if (pPos != std::string::npos && idPos != std::string::npos) {
						// Extract type
						texture.type = line.substr(2, pPos - 2);

						// Extract path
						texture.path = line.substr(pPos + 3, idPos - (pPos + 3));

						// Extract id
						try {
							texture.id = std::stoul(line.substr(idPos + 4));
						}
						catch (const std::exception&) {
							texture.id = 0;
						}

						meshData.textures.push_back(texture);
					}
				}
			}
		}

		// Only add meshData if it contains something meaningful
		if (!meshData.vertices.empty() || !meshData.indices.empty() || !meshData.textures.empty()) {
			meshResults.push_back(std::move(meshData));
		}
	}

	return meshResults;
}

std::optional<std::tuple<float, float, float>> ModelFactory::parse_xyz_fast(std::string_view s)
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
    if (!expect_char('X')) return std::nullopt;
    if (!expect_char(':')) return std::nullopt;
    if (!parse_double(x)) return std::nullopt;
    if (!expect_char('Y')) {
        // allow a separating space then 'Y'
        if (!expect_char(' ') || !expect_char('Y')) return std::nullopt;
    }
    if (!expect_char(':')) return std::nullopt;
    if (!parse_double(y)) return std::nullopt;
    if (!expect_char('Z')) {
        if (!expect_char(' ') || !expect_char('Z')) return std::nullopt;
    }
    if (!expect_char(':')) return std::nullopt;
    if (!parse_double(z)) return std::nullopt;
    return std::make_tuple(x, y, z);
}

//void ModelFactory::loadModelFile(std::string const& path)
//{
//
//    // read file via ASSIMP
//    Assimp::Importer importer;
//    // think of the scene as the whole 3D model or everything that is in the model file. It contains all the data of the 3D model. 
//    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
//    // check for errors
//    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
//    {
//        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
//        loadSuccessful = false;
//        return;
//    }
//    // retrieve the directory path of the filepath
//    directory = path.substr(0, path.find_last_of('/'));
//    // retrieve the model name (filename without extension)
//    modelData.modelName = path.substr(path.find_last_of('/') + 1, path.find_last_of('.') - path.find_last_of('/') - 1);
//
//    // process ASSIMP's root node recursively.
//    processNode(scene->mRootNode, scene);
//
//    loadSuccessful = true;
//}




