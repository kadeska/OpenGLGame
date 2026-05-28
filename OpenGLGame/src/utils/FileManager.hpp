#pragma once
//#include <iostream>
#include <string>


namespace FileManager 
{
	
	//typedef std::vector<std::optional<std::tuple<double, double, double>>> MeshResult;
	

	void createModelDataFolder();
	bool initDefaultModelDataFolder();
	bool saveDataToFileAtPath(const std::string _filename, const std::string _path, std::string _Data);
	bool exists(std::string filename);
	bool checkForModelDataFile(std::string modelPath);
	bool checkForModelDataFolder(std::string folderName);
	bool readDataFromFile(const std::string _filename, std::string& _outData);
	//std::vector<FileManager::MeshData> parseModelDataFolder(std::string folderName);
	
	void writeToBuffer(std::string data);
	bool saveBufferToFile(std::string fileName, std::string modelFolderName);
	
	void printBuffer();
	void clearBuffer();

	//std::optional<std::tuple<float, float, float>> parse_xyz_fast(std::string_view s);

}
