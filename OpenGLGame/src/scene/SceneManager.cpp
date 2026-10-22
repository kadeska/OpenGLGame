#include "SceneManager.hpp"


SceneManager::SceneManager(PhysicsManager* _physicsManager)
{
	this->physicsManager = _physicsManager;
}


// basiclly i initialize all the scenes here.
// for now i only have one scene, but i will add a main menu scene and make a level loader. 
// 
void SceneManager::initializeScenes()
{
	if (!physicsManager) 
	{
		log("Physics manager is null", LogType::ERROR);
		return;
	}

	//scene0 = createMainMenu();
	scene1 = createDefaultScene(physicsManager->createPhysicsWorld());

	// after we initialize all the scenes lets set the active scene to the main menu.
	activeScene = scene1; // set it to the default game scene for now untill i build a menu. 
}

Scene* SceneManager::createDefaultScene(rp3d::PhysicsWorld* _physicsWorld)
{
    Scene* scene = new Scene(_physicsWorld);
    scene->physicsWorld = _physicsWorld;
    return scene;
}
