#include "SceneManager.hpp"


SceneManager::SceneManager()
{
}

Scene* SceneManager::createDefaultScene()
{
    return new Scene();
}
