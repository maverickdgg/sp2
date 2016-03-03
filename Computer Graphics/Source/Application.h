#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Music.h"

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
	static void switchToScene3();
	static void playSound(int index, bool loop);

private:
	static Music* music;
	static Scene* scene;
	static Scene* scene1;
	static Scene* scene2;
	static Scene* scene3;
	//Declare a window object
	StopWatch m_timer;
};
#endif