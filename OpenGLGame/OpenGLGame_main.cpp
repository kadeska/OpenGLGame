// OpenGLGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// This project is a new starting point for making my openGL 3D game. Im not going to be making a game engine, 
// but instead build the game on top of my own abstraction that is built on OpenGL. OpenGL will be my API choice 
// for rendering, and I will be using GLFW for window/context management and input handling, GLAD for loading 
// OpenGL function pointers, GLM for mathematics, and Assimp for model loading, I will also be using stb_image
// for texture loading. I will use ImGui for both the in-game UI and the debug UI. I will be using C++20 or above as 
// the language standard, and I will be using Visual Studio 2026 as my IDE.

#include <iostream>


#include "src/rendering/DebugRenderer.hpp"
#include "src/glfw/glfwWindow.hpp"
//#include "src/rendering/RenderManager.hpp"
#include "src/game/GameManager.hpp"

#include "src/utils/Logger.hpp"
using namespace logger;

//#include <reactphysics3d/reactphysics3d.h>



OpenGLGame::GlfwWindow* m_window = nullptr;
//RenderManager* renderManager = nullptr;
GameManager* gameManager = nullptr;

bool debugRender = false;

void endProg()
{
    m_window->destroy();
    glfwTerminate();
    std::cout << "[END] Press Enter key to exit...\n" << std::cin.get();
}

// entry point
int main()
{
    // DRAFT::
    // 
    // atexit();
    // log();
    // window.create();
    // //regualrRenderer.create(window);
    // //debugRenderer.create(window); // if debugRender is true.
	// renderManager.create(window); // this will create the render manager, which will manage the regular and debug renderers, and it contains a render call that will use the appropriate renderer.
    // 
    // While shouldRender renderManager.render();
    // 





    std::atexit(endProg);
    log("Starting OpenGL Game...");
    // create a window and openGL context
    m_window = new OpenGLGame::GlfwWindow();
    m_window->create("Testing OpenGL", OpenGLGame::SCR_WIDTH, OpenGLGame::SCR_HEIGHT);

    if (!m_window) 
    {
        log("Failed to create GLFW window. ");
        return 1;
    }

    gameManager = new GameManager();

    gameManager->init(m_window);
    gameManager->update();
    

    // ToDO: I need to fix the physiscs update. 



	//renderManager = new RenderManager(m_window);
	//renderManager->create(m_window);

	//renderManager = new RenderManager(m_window);
	//renderManager->setDebugRender(debugRender);
	//renderManager->render();

	



    // build a scene.
	// what is a scene? a scene is a collection of models, lights, and other objects that make up the game world.
    //m_window.createScene();
    

    // check if debuf rendering is on.
   // if (debugRender) 
   // {
   //     if (debugRenderer == nullptr) 
   //     {
			//debugRenderer = new DebugRenderer();
			//log("DebugRenderer created.");
   //     }
   //     // do rendering here
   //     //return 0;
   // }

   // // start the main loop
   // m_window->startRender();
    // I feel like i should change this to be the renderer of choice is called here and the window is passed to the renderer. 

    return 0;
}