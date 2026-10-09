#include "SceneManager.hpp"


SceneManager::SceneManager()
{
}

void SceneManager::initializeScenes(rp3d::PhysicsWorld* _physicsWorld)
{
	//scene0 = createMainMenu();
	scene1 = createDefaultScene(_physicsWorld);

	// after we initialize all the scenes lets set the active scene to the main menu.
	activeScene = scene1; // set it to the default game scene for now untill i build a menu. 
}

Scene* SceneManager::createDefaultScene(rp3d::PhysicsWorld* _physicsWorld)
{
    Scene* scene = new Scene();
    scene->physicsWorld = _physicsWorld;
    return scene;
}
