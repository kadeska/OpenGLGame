#pragma once
//#include <iostream>
#include <string>


namespace FileManager 
{
		
	std::string getDefaultModelDataDir();
	// get the active model data dir.
	// TODO: Actually implement an active dir.
	std::string getActiveModelDataDir();


	void createModelDataFolder();
	bool initDefaultModelDataFolder();
	bool saveDataToFileAtPath(const std::string _filename, const std::string _path, std::string _Data);
	bool exists(std::string filename);
	bool checkForModelDataFile(std::string modelPath);
	bool checkForModelDataFolder(std::string folderName);
	bool readDataFromFile(const std::string _filename, std::string& _outData);
	
	void writeToBuffer(std::string data);
	bool saveBufferToFile(std::string fileName, std::string modelFolderName);
	
	void printBuffer();
	void clearBuffer();

}
