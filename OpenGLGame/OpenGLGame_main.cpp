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
    gameManager->startGame();
    

    // ToDO: I need to fix the game/physiscs update. 

    return 0;
}