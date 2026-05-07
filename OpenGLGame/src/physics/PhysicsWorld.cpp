#include "PhysicsWorld.hpp"

reactphysics3d::PhysicsWorld* world;

reactphysics3d::CollisionCallback* callbackptr;

PhysicsWorld::PhysicsWorld()
{
    std::cout << "Initializing physics world.\n";
    // First you need to create the PhysicsCommon object.
    // This is a factory module that you can use to create physics
    // world and other objects. It is also responsible for
    // logging and memory management
    //rp3d::PhysicsCommon physicsCommon;
	//physicsCommon = rp3d::PhysicsCommon();

    // settings

    // Create the world settings
    
    settings.defaultVelocitySolverNbIterations = 20;
    settings.isSleepingEnabled = false;
    settings.gravity = rp3d::Vector3(0, -500, 0);

    // Create a physics world with our settings
    world = physicsCommon.createPhysicsWorld(settings);
    world->setIsGravityEnabled(true);
    
    // default shape

    // Instanciate a sphere collision shape
    //sphereShape = physicsCommon.createSphereShape(10);

    // Keep a pointer to this object as a CollisionCallback to use with testCollision
    callbackptr = this;

}

reactphysics3d::PhysicsWorld* PhysicsWorld::getWorld()
{
    return world;
}
int y = 0;
void PhysicsWorld::update()
{
	std::cout << "Updating physics world." << std::endl;

    // Use a CollisionCallback reference as required by the API
    if (world && callbackptr) {
		world->getRigidBody(0)->setTransform(rp3d::Transform(rp3d::Vector3(0, y--, 0), rp3d::Quaternion::identity()));
        world->testCollision(*callbackptr);
        std::cout << "Rigid body Y position: " << world->getRigidBody(0)->getTransform().getPosition().y << std::endl;
    }
}

void PhysicsWorld::onContact(const reactphysics3d::CollisionCallback::CallbackData& callbackData)
{
    std::cout << "onContact() called." << std::endl;
}

PhysicsWorld::~PhysicsWorld()
{
    std::cout << "Destroying physics world.\n";
    if (world) {
        physicsCommon.destroyPhysicsWorld(world);
        world = nullptr;
    }
}
