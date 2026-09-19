#pragma once
#include <string>

#include "Scene.hpp"

class SceneManager
{
public:

	SceneManager();
	~SceneManager();

	Scene* createDefaultScene();
	//void createScene(std::string sceneName, std::vector<> model);
	void loadSceneFromFile(std::string filename);
	void saveSceneToFile(std::string filename);
};

