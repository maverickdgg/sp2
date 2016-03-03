/******************************************************************************/
/*!
\file	Application.h
\author Daniel Chua
\par	Email: 152112Y@mymail.nyp.edu.sg
\par	Admin Number: 152112Y
\par	School: Nanyang Polytechnic (School of Interactive and Digital Media)
\par	Diploma: Game Development and Technology
\par	Class: GD1503
\par	Mobile Number: 9025 8239
\brief
Class to define Application
*/
/******************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>
#include "Scene.h"
#include "Music.h"
/******************************************************************************/
/*!
Class Application:
\brief
Class for Application
/******************************************************************************/
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