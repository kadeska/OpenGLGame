#pragma once
#include <string>

#include "Scene.hpp"

class SceneManager
{
private:

	// currntly active scene
	Scene* activeScene = nullptr;

	// main menu
	Scene* scene0 = nullptr;

	// gameplay scene
	Scene* scene1 = nullptr;

public:

	SceneManager();
	~SceneManager();

	void initializeScenes(rp3d::PhysicsWorld* _physicsWorld);
	Scene* getActiveScene() { return activeScene; }
	void setActiveScene(Scene* scene) { activeScene = scene; }

	Scene* createDefaultScene(rp3d::PhysicsWorld* _physicsWorld);
	//void createScene(std::string sceneName, std::vector<> model);
	void loadSceneFromFile(std::string filename);
	void saveSceneToFile(std::string filename);
};

