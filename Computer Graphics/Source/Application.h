#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>
#include "Scene.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);

	static void switchToScene1();
	static void switchToScene2();

private:
	static Scene* scene;
	static Scene* scene1;
	static Scene* scene2;
	//Declare a window object
	StopWatch m_timer;
};
#endif