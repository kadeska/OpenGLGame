#include "FileManager.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
//#include <map>



// --- Global/Static Data ---
std::string fileBuffer;

struct DefaultValues {
	std::string defaultModelDataDir = "appData/modelData";
} defaults;



std::string FileManager::getDefaultModelDataDir()
{
	return defaults.defaultModelDataDir;
}

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



// --- Buffer Functions ---

bool FileManager::saveBufferToFile(std::string fileName, std::string modelFolderName)
{
	return saveDataToFileAtPath(fileName, defaults.defaultModelDataDir + "/" + modelFolderName + "/", fileBuffer);
}

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