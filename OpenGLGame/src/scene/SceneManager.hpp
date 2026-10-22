#pragma once
#include <string>

#include "Scene.hpp"

#include "../physics/PhysicsManager.hpp"


// there should only be one SceneManager for the whole game.
class SceneManager
{
private:
	// This is a pointer to our physics manager, which is responsible for managing the physics worlds and updating the physics simulation.
	// There should only be one physics manager for the whole game, and it should be passed to the scene manager so that it can create and manage physics worlds for each scene.
	PhysicsManager* physicsManager;

	// currntly active scene
	Scene* activeScene = nullptr;

	// main menu
	Scene* scene0 = nullptr;

	// gameplay scene
	Scene* scene1 = nullptr;

public:
	// constructor takes a physics manager pointer to use for this scene manager. 
	SceneManager(PhysicsManager* physicsManager);
	~SceneManager();

	void initializeScenes();
	Scene* getActiveScene() { return activeScene; }
	void setActiveScene(Scene* scene) { activeScene = scene; }

	Scene* createDefaultScene(rp3d::PhysicsWorld* _physicsWorld);
	//void createScene(std::string sceneName, std::vector<> model);
	void loadSceneFromFile(std::string filename);
	void saveSceneToFile(std::string filename);
};

