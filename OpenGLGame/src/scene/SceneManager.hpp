#pragma once
#include <string>
class SceneManager
{
	SceneManager();
	~SceneManager();

	void createDefaultScene();
	//void createScene(std::string sceneName, std::vector<> model);
	void loadSceneFromFile(std::string filename);
	void saveSceneToFile(std::string filename);
};

