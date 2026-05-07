#pragma once
#include <iostream>
#include <string>
#include <fstream>

namespace FileManager 
{
	// returns 0 if path was created, 1 if path already exists, -1 if failed to create path
	int initModelDataFolder();
	bool createDirectory(std::string dir);
	bool createDirectorys(std::string path);

	bool filePathExists(std::string filePathName);
	
	bool saveToFile(std::string _fileName, std::string data);
	void saveToBuffer(std::string data);
	bool saveBufferToFile(std::string fileName);

	//[[deprecated("Use checkForModelDataFiles instead")]]
	int readDataFromFile(const std::string& _filename, std::string& _outData);
	
	//[[deprecated("Use checkForModelDataFiles instead")]]
	int loadDataFile(const std::string& fileName);
	//void saveToBuffer(std::vector<Vertex> vertices, std::vector<unsigned int> indices, textures);
	
	void printBuffer();
	void clearBuffer();
	
	
	// this function will check if the data files for the models are available, and if not then it will call a function that generates them from the models and saves them to files.
	bool checkForModelDataFiles(const std::string& path);



}
