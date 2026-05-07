// OpenGLGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// This project is a new starting point for making my openGL 3D game. Im not going to be making a game engine, 
// but instead build the game on top of my own abstraction that is built on OpenGL. OpenGL will be my API choice 
// for rendering, and I will be using GLFW for window/context management and input handling, GLAD for loading 
// OpenGL function pointers, GLM for mathematics, and Assimp for model loading, I will also be using stb_image
// for texture loading. I will use ImGui for both the in-game UI and the debug UI. I will be using C++20 or above as 
// the language standard, and I will be using Visual Studio 2026 as my IDE.

#include <iostream>

#include "src/glfw/glfwWindow.hpp"

//#include <reactphysics3d/reactphysics3d.h>

OpenGLGame::GlfwWindow m_window;

void endProg()
{
    m_window.destroy();
    glfwTerminate();
    std::cout << "[END] Press Enter key to exit...\n" << std::cin.get();
}

int main()
{
    std::atexit(endProg);

    std::cout << "Hello World!\n" << std::endl;

    //// First you need to create the PhysicsCommon object.
    //// This is a factory module that you can use to create physics
    //// world and other objects. It is also responsible for
    //// logging and memory management
    //rp3d::PhysicsCommon physicsCommon;

    //// Create a physics world
    //rp3d::PhysicsWorld* world = physicsCommon.createPhysicsWorld();

    //// Create a rigid body in the world
    //rp3d::Vector3 position(0, 20, 0);
    //rp3d::Quaternion orientation = rp3d::Quaternion::identity();
    //rp3d::Transform transform(position, orientation);
    //rp3d::RigidBody* body = world->createRigidBody(transform);

    //const rp3d::decimal timeStep = 1.0f / 60.0f;

    //// Step the simulation a few steps
    //for (int i = 0; i < 20; i++) {

    //    world->update(timeStep);

    //    // Get the updated position of the body
    //    const rp3d::Transform& transform = body->getTransform();
    //    const rp3d::Vector3& position = transform.getPosition();

    //    // Display the position of the body
    //    std::cout << "Body Position: (" << position.x << ", " <<
    //        position.y << ", " << position.z << ")" << std::endl;
    //}

    //m_window.createScene();
    
    if (!m_window.create("Testing OpenGL", OpenGLGame::SCR_WIDTH, OpenGLGame::SCR_HEIGHT)) 
    {
		std::cout << "Failed to create window" << std::endl;
        return 1;
    }

    // build a scene.
	// what is a scene? a scene is a collection of models, lights, and other objects that make up the game world.
    //m_window.createScene();
    

    m_window.startRender();


    //m_window.destroy();
    //glfwTerminate();
    

    //std::cout << "[END] Press Enter key to exit...\n" << std::cin.get();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
