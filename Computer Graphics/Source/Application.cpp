#include "Application.h"


//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SP2_Scene1.h"
#include "Sp2_SpaceRace.h"
#include "SP2_Scene3.h"



GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

Scene* Application::scene;
Scene* Application::scene1;
Scene* Application::scene2;
Scene* Application::scene3;

Music* Application::music;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
	return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

Application::Application()
{
}

Application::~Application()
{
}

void resize_callback(GLFWwindow *window, int w, int h)
{
	glViewport(0, 0, w, h); //update OpenGL the new window size.
}



void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context

	//m_window = glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width, glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "Computer Graphics", glfwGetPrimaryMonitor(), NULL);
	m_window = glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width, glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "Computer Graphics", NULL, NULL);
	//m_window = glfwCreateWindow(1980, 1080, "Computer Graphics", glfwGetPrimaryMonitor() , NULL);

	glfwSetWindowSizeCallback(m_window, resize_callback);

	

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}



	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	glfwSetKeyCallback(m_window, key_callback);


	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}
}

void Application::switchToScene1()
{
	scene = scene1;
}

void Application::switchToScene2()
{
	scene = scene2;
}

void Application::switchToScene3()
{
	scene = scene3;
}



void Application::playSound(int index, bool loop)
{
	music->OpeningMusic(index,loop);
}

void Application::Run()
{
	//Main Loop

	music = new Music();
	music->Init();

	scene3 = new Sp2_Scene3();
	scene3->Init();

	scene2 = new Sp2_SpaceRace();
	scene2->Init();

	scene1 = new Sp2_Scene1();
	scene1->Init();

	scene = scene3;

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE))
	{
		if (Application::IsKeyPressed('R'))
		{
			scene1->Reset();
			scene2->Reset();
			scene3->Reset();
			switchToScene1();
		}

		scene->Update(m_timer.getElapsedTime());
		scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
		m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	scene->Exit();
	delete scene1;
	delete scene2;
	delete scene3;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
