#pragma once
#include "glfwIncludes.hpp"

//#include "../shader.hpp"
//#include "../camera/camera.hpp"
#include "../model/model.hpp"




void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

void processInput(GLFWwindow* window);

namespace LearnOpenGLProj
{


	//----------------------settings----------------------------
	// These settings can be changed to adjust the window size and other parameters.
	//----------------------------------------------------------
	const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;
	//----------------------------------------------------------


	// GLFW window class for managing the GLFW window and its OpenGL context.
	class GlfwWindow
	{
	private:
		// this array is basically our "scene"
		//std::vector<ModelInstance*> models;
	public:
		GlfwWindow();
		~GlfwWindow() = default;
		
		// creates a GLFW window and its OpenGL context, and sets up all the required OpenGL function pointers.
		// Also creates the scene(s) and the shader program. Returns true if the window was created successfully, false otherwise.
		bool create(const char* title, int width, int height);
		bool createScene();
		// this function contains the main render loop.
		void startRender();
		void destroy();
		// returns the current GLFWwindow pointer, which can be used for input processing and other GLFW functions that require the window pointer.
		GLFWwindow* get() const { return window; }
	private:
		GLFWwindow* window = nullptr;
		Shader* myShader = nullptr;
		
	private:
		bool initGlad();
		bool initGLFW();
		bool makeShaderProgram();
		// this function calls the render functions for all the models
		void render();
		
	};
}