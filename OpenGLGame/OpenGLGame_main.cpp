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
    
    if (!m_window.create("Testing OpenGL", OpenGLGame::SCR_WIDTH, OpenGLGame::SCR_HEIGHT)) 
    {
		std::cout << "Failed to create window" << std::endl;
        return 1;
    }

    // build a scene.
	// what is a scene? a scene is a collection of models, lights, and other objects that make up the game world.
    //m_window.createScene();
    

    m_window.startRender();

    return 0;
}