#include <iostream>
#include <chrono>

#include "glfwWindow.hpp"
#include "../camera/camera.hpp"
#include "../model/ModelInstance.hpp"
#include "../scene/Scene.hpp"


// signals
bool shouldRender = true;


// models

//LearnOpenGLProj::ModelInstance* modelA = nullptr;// = new LearnOpenGLProj::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
//LearnOpenGLProj::ModelInstance* modelB = nullptr;// = new LearnOpenGLProj::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(100.0f, 100.0f, 100.0f), glm::vec3(1.0f));

// scene
Scene* scene = nullptr;


// camera

Camera* camera = nullptr;// (glm::vec3(0.0f, 0.0f, 3.0f))
bool firstMouse = true;
float lastX = OpenGLGame::SCR_WIDTH / 2.0f;
float lastY = OpenGLGame::SCR_HEIGHT / 2.0f;

// model
//Model* ourModel = nullptr;

// timing

float deltaTime = 0.0f;
float lastFrame = 0.0f;


// Returns current system time in seconds (high-resolution) as a long double.
static long double getCurrentSystemTime()
{
    using namespace std::chrono;
    return duration_cast<duration<long double>>(high_resolution_clock::now().time_since_epoch()).count();
}

bool OpenGLGame::GlfwWindow::initGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

bool OpenGLGame::GlfwWindow::initGLFW()
{
    if (!glfwInit()) 
    {
		std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    return true;
}

bool OpenGLGame::GlfwWindow::makeShaderProgram()
{
	std::cout << "Making shader program..." << std::endl;
    myShader = new Shader("vertex.shader", "fragment.shader");

    return myShader;
}

void OpenGLGame::GlfwWindow::render()
{
    //----------------------------------------------------------------------------------------------------------------------------------
	// before i can render the scene I need to do physics simulation step and update the models positions based on the physics simulation results. 
    // This is important because the models positions are used in the vertex shader to render the models in the correct position in the world, 
    // and they are also used for collision detection and response. If I don't update the models positions based on the physics simulation results, 
    // then the models will not be rendered in the correct position in the world, and they will not collide with each other correctly. 
    // So I need to do the physics simulation step before rendering the scene, and I need to update the models positions based on the physics 
    // simulation results before rendering the scene.
    //----------------------------------------------------------------------------------------------------------------------------------   
	
    if ((scene != nullptr) && shouldRender) 
    {
        if (myShader == nullptr) 
        {
			std::cout << "[!Warning!] | GlfwWindow::render() | Shader is nullptr, cannot render!" << std::endl;
            return;
        }
        myShader->use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera->GetViewMatrix();
        myShader->setMat4("projection", projection);
        myShader->setMat4("view", view);

        // physics simulation -------------------
		
        scene->update();

        // render the scene ---------------------

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render all model instances in the models std::vector.
        for (ModelInstance::ModelInstance* modelInstance : scene->getModels())
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, modelInstance->position);
            model = glm::scale(model, modelInstance->scale);
            //model = glm::translate(model, modelInstance->position) = glm::scale(model, modelInstance->scale);
            myShader->setMat4("model", model);

            // draw call
            modelInstance->model->Draw(myShader);


        }
    }
    else 
    {
		std::cout << "[!Warning!] | GlfwWindow::render() | Scene is nullptr, cannot render!" << std::endl;
        shouldRender = false;
        return;
    }

    
}

OpenGLGame::GlfwWindow::GlfwWindow()
{
    camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

bool OpenGLGame::GlfwWindow::create(const char* title, int width, int height)
{

    initGLFW();

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // do this after loading is compleate, otherwise the mouse will be locked pretty much at the start of the program. 

    initGlad();

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // make shader
    if (!makeShaderProgram()) 
    {
		std::cout << "Failed to create shader program" << std::endl;
    }

    // load models
    // -----------
    //ourModel = new Model("res/obj/backpack/backpack.obj");
	//models.push_back(new LearnOpenGLProj::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	//models.push_back(new LearnOpenGLProj::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f)));
	//modelA = new LearnOpenGLProj::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(5.0f, 5.0f, 2.0f), glm::vec3(1.0f));
	//modelB = new LearnOpenGLProj::ModelInstance("res/obj/backpack/backpack.obj", glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));
	//models.push_back(modelA);
	//models.push_back(modelB);

    //if (!ourModel->loadSuccessful) 
    //{
    //    delete ourModel;
    //    ourModel = nullptr;
    //    return false;
    //}

    //create a scene
    createScene();

    // add a check here if the scene is null then we can send a debug message
    if (scene == nullptr)
    {
        std::cout << "[!Warning!] Scene is nullptr!" << std::endl;
    }

	return true;
}

bool OpenGLGame::GlfwWindow::createScene()
{
	scene = new Scene();

    return true;
}


// timing helpers for fixed timestep loop
static long double previousFrameTime = getCurrentSystemTime();
static long double accumulator = 0.0L;

void OpenGLGame::GlfwWindow::startRender()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // put this here so the mouse is only captured when we want to actually start rendering. 

    // Constant physics time step
    const float timeStep = 1.0f / 60.0f;

    // Get the current system time
    long double currentFrameTime = getCurrentSystemTime();

    // Compute the time difference between the two frames
    long double deltaTime = currentFrameTime - previousFrameTime;

    // Update the previous time
    previousFrameTime = currentFrameTime;

    // Add the time difference in the accumulator
    accumulator += deltaTime;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // (Optional) perform fixed-step updates here
        while (accumulator >= timeStep)
        {   
            // render
            if (shouldRender)
            {
                // Update the Dynamics world with a constant time step
                // and then render
                render();
                glfwSwapBuffers(window);
            }

            // Decrease the accumulated time
            accumulator -= timeStep;
        }

        // input
        // -----
        processInput(window);

        
        glfwPollEvents();

        // Add the time difference to the accumulator for fixed-step updates
        accumulator += timeStep;
    }
}

void OpenGLGame::GlfwWindow::destroy()
{
    if (myShader)
    {
        delete myShader;
        //myShader = nullptr;
    }
    if (camera)
    {
        delete camera;
        //camera = nullptr;
    }
    //glDeleteVertexArrays(1, &VAO);
    //glDeleteBuffers(1, &VBO);
    //glDeleteProgram(shaderProgram);
    glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
        
}
