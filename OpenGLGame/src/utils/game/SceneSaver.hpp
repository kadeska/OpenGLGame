#pragma once
#include "../../scene/Scene.hpp"
class SceneSaver
{
private:
	std::string sceneFilePath = "appData/scenes/sceneData.txt";
public:
	SceneSaver();
	~SceneSaver();

	// Saves the given scene to the default scene file path.
	void saveScene(Scene* scene);
	// Saves the given scene to the given scene file path.
	void saveSceneTo(Scene* scene, std::string sceneFilePath);
	// Loads the scene of the given name from the default scene file path and returns a pointer to the loaded scene.
	Scene* loadScene(std::string sceneFileName);
	// Loads the scene of the given name from the specified scene file path and returns a pointer to the loaded scene.
	Scene* loadSceneFrom(std::string sceneFileName, std::string sceneFilePath);

};

