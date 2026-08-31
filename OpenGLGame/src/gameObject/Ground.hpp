#pragma once
#include "GameObjectBase.hpp"
class Ground : public GameObjectBase
{
public:
	Ground() 
	{
		init(GameObjectType::GROUND);
	}
};

