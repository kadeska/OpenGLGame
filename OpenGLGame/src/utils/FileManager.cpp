#include "FileManager.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
//#include <map>



// --- Global/Static Data ---
std::string fileBuffer;

struct Defaults {
    std::string defaultModelDataDir = "appData/modelData";
} defaults;



void FileManager::createModelDataFolder()
{
	if (!std::filesystem::create_directories(defaults.defaultModelDataDir)) {}
}

bool FileManager::initDefaultModelDataFolder()
{
    if (!std::filesystem::create_directories(defaults.defaultModelDataDir)) 
    {
        std::cout << "Directory already exists: " << defaults.defaultModelDataDir << std::endl;
		return false;
    }

	std::cout << "Directory created: " << defaults.defaultModelDataDir << std::endl;
    return true;
}

bool FileManager::saveDataToFileAtPath(const std::string _filename = "default", const std::string _path = defaults.defaultModelDataDir, std::string _Data = "")
{
	std::ofstream file(_path + "/" + _filename);
	if (!file)
	{
		std::cout << "Failed to open file: " << _path + "/" + _filename << std::endl;
		return false;
	}
	file << _Data;
	file.close();
	return true;
}

// --- File Existence/Check Functions ---
bool FileManager::exists(std::string filename_path) // takes a filename or path and checks if it exists in the default model data directory
{
    std::filesystem::path p = defaults.defaultModelDataDir + "/" + filename_path;
	return std::filesystem::exists(p);
}

bool FileManager::checkForModelDataFile(std::string filename)
{
	// cheack if the path exists
	if (!exists(filename)) // treat this filename as a folder name
	{
		std::cout << "Model data folder not found for model: " << filename << " at path: " << defaults.defaultModelDataDir << std::endl;
		return false;
	}
	// 
	// Actually now we need to loop through the files in this folder and for each file, make a Mesh object from its data.
	// 
	// check if the file exists
	//if (!std::filesystem::exists(defaults.defaultModelDataDir + "/" + filename))
	//{
	//	std::cout << "Model data folder not found for model: " << filename << " at path: " << defaults.defaultModelDataDir << std::endl;
	//	return false;
	//}

	std::cout << "Model data file found for model: " << filename << " at path: " << defaults.defaultModelDataDir << std::endl;
	return true;
}

bool FileManager::checkForModelDataFolder(std::string folderName)
{
	if(!exists(folderName + "/"))
	{
		std::cout << "Model data folder not found for model: " << folderName << " at path: " << defaults.defaultModelDataDir << std::endl;
		return false;
	}
	std::cout << "Model data folder found for model: " << folderName << " at path: " << defaults.defaultModelDataDir << std::endl;
	return true;
}

bool FileManager::readDataFromFile(const std::string _filename, std::string& _outData)
{
	std::string data;
	std::string line;
	std::ifstream dataFile(defaults.defaultModelDataDir + "/" + _filename);
	if (dataFile.is_open()) 
	{
		while (std::getline(dataFile, line)) 
		{
			data += line + "\n";
		}
		dataFile.close();
		_outData = data;
		return true;
	}
	return false;
}


// --- define nested MeshData so FileManager::MeshData is a complete type (was previously a file-local struct) ---
//struct FileManager::MeshData
//{
//    struct Texture
//    {
//        unsigned int id;
//        std::string type;
//        std::string path;
//    };
//
//    struct Vertex
//    {
//        std::vector<float> Position;
//        std::vector<float> Normal;
//        std::vector<float> TexCoords;
//        std::vector<float> Tangent;
//        std::vector<float> Bitangent;
//        int m_BoneIDs[4];
//        float m_Weights[4];
//
//        Vertex()
//        {
//            Position.clear();
//            Normal.clear();
//            TexCoords.clear();
//            Tangent.clear();
//            Bitangent.clear();
//            for (int i = 0; i < 4; ++i) {
//                m_BoneIDs[i] = 0;
//                m_Weights[i] = 0.0f;
//            }
//        }
//    };
//
//    std::vector<Vertex> vertices;
//    std::vector<unsigned int> indices;
//    std::vector<Texture> textures;
//};



// --- parseModelDataFolder: build one MeshData per file, initialize locals, and return results ---
//std::vector<FileManager::MeshData> FileManager::parseModelDataFolder(std::string folderName)
//{
//	namespace fs = std::filesystem;
//
//	const fs::path folder = defaults.defaultModelDataDir + "/" + folderName;
//
//	std::vector<MeshData> meshResults;
//
//	// this for loop goes through each file in the folder
//	for (auto const& entry : fs::directory_iterator(folder)) {
//		if (!entry.is_regular_file()) continue;
//
//		// Optionally filter by extension:
//		//if (entry.path().extension() != ".txt") continue;
//
//		std::ifstream in(entry.path());
//		if (!in) {
//			std::cerr << "Failed to open: " << entry.path() << '\n';
//			continue;
//		}
//
//		MeshData meshData; // one mesh per file
//		std::string line;
//		while (std::getline(in, line)) {
//			std::string_view v(line);
//			if (auto t = parse_xyz_fast(v)) {
//				auto [x, y, z] = *t;
//				MeshData::Vertex vertex{};
//				vertex.Position = {x,y,z};
//				meshData.vertices.push_back(std::move(vertex));
//			}
//			else {
//				// ignore non-parsable lines
//			}
//		}
//
//		// Only add meshData if it contains something meaningful
//		if (!meshData.vertices.empty() || !meshData.indices.empty() || !meshData.textures.empty()) {
//			meshResults.push_back(std::move(meshData));
//		}
//	}
//
//	return meshResults;
//}

bool FileManager::saveBufferToFile(std::string fileName, std::string modelFolderName)
{
	return saveDataToFileAtPath(fileName, defaults.defaultModelDataDir + "/" + modelFolderName + "/", fileBuffer);
}

// --- Buffer Functions ---
void FileManager::writeToBuffer(std::string data)
{
    fileBuffer += data;
}

void FileManager::clearBuffer()
{
    fileBuffer.clear();
}

void FileManager::printBuffer()
{
    std::cout << "Buffer content:\n" << fileBuffer << std::endl;
}

//std::optional<std::tuple<float, float, float>> FileManager::parse_xyz_fast(std::string_view s) {
//	auto skip_spaces = [&]() {
//		while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front()))) s.remove_prefix(1);
//		};
//	auto expect_char = [&](char ch)->bool {
//		skip_spaces();
//		if (s.empty() || s.front() != ch) return false;
//		s.remove_prefix(1);
//		return true;
//		};
//	auto parse_double = [&](double& out)->bool {
//		skip_spaces();
//		if (s.empty()) return false;
//		const char* begin = s.data();
//		std::from_chars_result r = std::from_chars(begin, begin + s.size(), out);
//		if (r.ec != std::errc()) return false;
//		size_t consumed = r.ptr - begin;
//		s.remove_prefix(consumed);
//		return true;
//		};
//
//	double x, y, z;
//	if (!expect_char('X')) return std::nullopt;
//	if (!expect_char(':')) return std::nullopt;
//	if (!parse_double(x)) return std::nullopt;
//	if (!expect_char('Y')) {
//		// allow a separating space then 'Y'
//		if (!expect_char(' ') || !expect_char('Y')) return std::nullopt;
//	}
//	if (!expect_char(':')) return std::nullopt;
//	if (!parse_double(y)) return std::nullopt;
//	if (!expect_char('Z')) {
//		if (!expect_char(' ') || !expect_char('Z')) return std::nullopt;
//	}
//	if (!expect_char(':')) return std::nullopt;
//	if (!parse_double(z)) return std::nullopt;
//	return std::make_tuple(x, y, z);
//}