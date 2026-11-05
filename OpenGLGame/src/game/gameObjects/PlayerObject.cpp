#include "PlayerObject.hpp"

PlayerObject::PlayerObject(ModelInstance::ModelInstance* modelInstance) : GameObjectCore(modelInstance) 
{

}

void PlayerObject::printID()
{
	std::cout << "Player" << id << std::endl;
}