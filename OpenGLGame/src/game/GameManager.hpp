#pragma once
//#include "../physics/PhysicsManager.hpp"
#include "../rendering/RenderManager.hpp"
#include "../scene/SceneManager.hpp"


class GameManager
{
private:
	RenderManager* renderManager = nullptr;
	SceneManager* sceneManager = nullptr;
	Scene* activeScene = nullptr;
public:
	GameManager();
	~GameManager();

	void init();
	void update();
	void render();
};

