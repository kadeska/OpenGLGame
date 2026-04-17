#pragma once
#include "model.hpp"
#include "../utils/FileManager.hpp"

namespace ModelInstance
{
    // ModelInstance structure to hold model data and transformation information
    struct ModelInstance
    {
        Model* model;
        glm::vec3 position;
        glm::vec3 scale;

        ModelInstance(const char* path, glm::vec3 pos = glm::vec3(0.0f), glm::vec3 scl = glm::vec3(1.0f))
            : position(pos), scale(scl)
        {
            //std::string out;
			// do a check here if we have this models data already loaded into a file for faster loading.
    //        if (readDataFromFile("file", out)) 
    //        {
				//std::cout << "Failed to read data from file, loading model from path: " << path << std::endl;
    //        }

			//FileManager::fileExists(path);
            //std::string outdata;
            //FileManager::readDataFromFile("modelData.txt", outdata);

            model = new Model(path);
        }

        ~ModelInstance()
        {
            if (model) delete model;
        }
    };

    //int readDataFromFile(const std::string& _filename, std::string& _outData)
    //{
    //    std::cout << "Reading data from file: " << _filename;
    //    std::string content;
    //    std::string line;
    //    int lineCount = 0;
    //    std::ifstream MyReadFile(_filename);
    //    if (!MyReadFile)
    //    {
    //        std::cout << "Failed to open file: " << _filename;
    //        return -1; // indicate failure to open file
    //    }
    //    while (getline(MyReadFile, line)) {
    //        content.append(line + '\n');
    //        lineCount++;
    //    }
    //    MyReadFile.close();
    //    _outData = content;
    //    if (content.empty()) { return 1; }
    //    return 0;
    //}
}

