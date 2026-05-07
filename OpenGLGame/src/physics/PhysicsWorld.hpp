#pragma once
#include <reactphysics3d/reactphysics3d.h>

class PhysicsWorld : public reactphysics3d::CollisionCallback
{
public:
	PhysicsWorld();
	~PhysicsWorld();
	reactphysics3d::PhysicsWorld* getWorld();


	void update();

	// Correctly override the pure virtual from reactphysics3d::CollisionCallback
	virtual void onContact(const reactphysics3d::CollisionCallback::CallbackData& callbackData) override;

private:
	rp3d::PhysicsCommon physicsCommon;           // keep it alive
	rp3d::PhysicsWorld::WorldSettings settings;
	rp3d::PhysicsWorld* world;         // created from mPhysicsCommon
	
	// ...
};

