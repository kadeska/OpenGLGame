#include "FileManager.hpp"

#include <filesystem>
#include <map>

// --- Global/Static Data ---
std::string fileBuffer;

struct Defaults {
    std::string defaultModelDataDir = "modeldata";
} defaults;

// --- Utility/Helper Functions ---
inline int saveDataToFile(const std::string _filename, std::string _Data)
{
    std::cout << "Saving data to file: " << _filename << std::endl;
    std::ofstream MyFile(_filename);
    MyFile << _Data.c_str();
    MyFile.close();
    return 0;
}

// --- File Existence/Check Functions ---
bool FileManager::fileExists(std::string _fileName)
{
    std::ifstream MyReadFile(_fileName);
    if (!MyReadFile)
    {
        std::cout << "cant locate file: " << _fileName << std::endl;
        return false;
    }
    std::cout << "File found: " << _fileName << std::endl;
    return true;
}

// --- File Write Functions ---
bool FileManager::saveToFile(std::string _fileName, std::string data)
{
    std::cout << "Saving to file: " << _fileName << std::endl; 
    std::ofstream myFile(_fileName);
    myFile << data;
    myFile.close();
    return true;
}

bool FileManager::saveBufferToFile(std::string fileName)
{
    std::string path = defaults.defaultModelDataDir + "/" + fileName;
    std::ofstream myFile(path);
    if (!myFile)
    {
        std::cout << "Failed to open file: " << path << std::endl;
        return false;
    }
    myFile << fileBuffer;
    myFile.close();
    return true;
}

// --- File Read Functions ---
int FileManager::readDataFromFile(const std::string& _filename, std::string& _outData)
{
    std::cout << "Reading data from file: " << _filename << std::endl;
    std::string content;
    std::string line;
    int lineCount = 0;
    std::ifstream MyReadFile(_filename);
    if (!MyReadFile)
    {
        std::cout << "Failed to open file: " << _filename << std::endl;
        return -1; // indicate failure to open file
    }
    while (getline(MyReadFile, line)) {
        content.append(line + '\n');
        lineCount++;
    }
    MyReadFile.close();
    _outData = content;
    if (content.empty()) { return 1; }
    return 0;
}

int FileManager::loadDataFile(const std::string& fileName)
{
    std::cout << "Attempting to load model data from file: " << fileName << std::endl;
    std::string outdata;
    if (readDataFromFile(fileName, outdata) == 0)
    {
        std::cout << "successfull read. Using data from file\n";
        std::cout << "data from file: \n" << outdata << std::endl;
        return true;
    }
    else
    {
        std::cout << "failed to read. Using default data\n";
        std::cout << "attempting to create file with default data\n";
        std::string defaultContent = "new file";
        saveToFile(fileName, defaultContent);
        loadDataFile(fileName);
        return false;
    }
}

// --- Buffer Functions ---
void FileManager::saveToBuffer(std::string data)
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

// --- Directory/Folder Functions ---
int FileManager::initModelDataFolder()
{
    std::string path = defaults.defaultModelDataDir;
    std::filesystem::path dir(path);
    if (std::filesystem::create_directory(dir))
    {
        std::cout << "Directory '" << path << "' created successfully." << std::endl;
        return 0; // path was created
    } else if (std::filesystem::exists(dir))
    {
        std::cout << "Directory '" << path << "' already exists." << std::endl;
        return 1; // path already exists
    } 
    else
    {
        std::cout << "Failed to create directory '" << path << "'." << std::endl;
    }
    return -1; // failed to create directory
}

bool FileManager::createDirectory(std::string dir)
{
    std::filesystem::path path(dir);
    if (std::filesystem::create_directory(path))
    {
        std::cout << "Directory '" << dir << "' created successfully." << std::endl;
        return true;
    }
    else if (std::filesystem::exists(path))
    {
        std::cout << "Directory '" << dir << "' already exists." << std::endl;
        return true;
    }
    else
    {
        std::cout << "Failed to create directory '" << dir << "'." << std::endl;
        return false;
    }
}

// --- Batch/Model Data File Check Functions ---
bool FileManager::checkForModelDataFiles(const std::string& path)
{
    std::cout << "Checking for model data files..." << std::endl;
    return false;
}
