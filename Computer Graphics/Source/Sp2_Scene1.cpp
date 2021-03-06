#include "Sp2_Scene1.h"
#include "Human.h"
#include "Alien.h"
#include "BB-8.h"
#include "Pingu.h"
#include "GL\glew.h"
#include "Buildings.h"

#include "shader.hpp"
#include "LoadTGA.h"
#include "Collision.h"
#include "Application.h"

extern GLFWwindow* m_window;

Sp2_Scene1::Sp2_Scene1()
{
	
}

Sp2_Scene1::~Sp2_Scene1()
{
	player.questList.clear();
}
/******************************************************************************/
/*!
\brief
initialise of the scene
*/
/******************************************************************************/
void Sp2_Scene1::Init()
{
	Application::playSound(4, true);
	ShowCursor(FALSE);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//enable depth test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// generate a default VAO
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// generate buffers
	glGenBuffers(NUM_GEOMETRY, &m_vertexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_indexBuffer[0]);
	glGenBuffers(NUM_GEOMETRY, &m_colorBuffer[0]);

	glfwGetWindowSize(m_window, &screenWidth, &screenHeight);
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");


	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");


	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].color.Set(1, 0.9f, 1);
	light[0].position.Set(0.f, 20.f, 0.f);
	light[0].power = 1.f;
	light[0].kC = 1.f;
	light[0].kL = 0.0001f;
	light[0].kQ = 0.00001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(15));
	light[0].cosInner = cos(Math::DegreeToRadian(10));
	light[0].exponent = 1.f;
	light[0].spotDirection.Set(0.0f, 1.0f, 0.0f);


	// Pass information
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	
	//geom init

	camera.Init(Vector3(0, 0, 0), Vector3(10, 0, 0), Vector3(0, 1, 0), 450, 300);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("AXES", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f, 1.f);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//purplenebula_ft.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//Assn3_bottom.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//purplenebula_bk.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//purplenebula_up.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//purplenebula_lf.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//purplenebula_rt.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("LIGHTBALL", Color(1, 0, 1));

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT2] = MeshBuilder::GenerateText("text2", 16, 16);
	meshList[GEO_TEXT2]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_TEXTBACKGROUND] = MeshBuilder::GenerateQuad("quad", Color(0, 0, 1), 1.f, 1.f);

	/*<---Studio Project 2 OBJs--->*/

	meshList[GEO_NPCLEPUSMAG] = MeshBuilder::GenerateOBJ("NPCLEPUSMAG", "OBJ//NPCLEPUSMAG.obj");
	meshList[GEO_NPCLEPUSMAG]->textureID = LoadTGA("Image//NPCLEPUSMAG.tga");

	meshList[GEO_FOURTH] = MeshBuilder::GenerateOBJ("fourthplayercontrolled", "OBJ//FourthPlayerControlled.obj");
	meshList[GEO_FOURTH]->textureID = LoadTGA("Image//FourthPlayerControlled.tga");

	/*<---NPC--->*/
	meshList[GEO_MIKE] = MeshBuilder::GenerateOBJ("npc1", "OBJ//mike.obj");
	meshList[GEO_MIKE]->textureID = LoadTGA("Image//mike.tga");

	meshList[GEO_STATION] = MeshBuilder::GenerateOBJ("spacestation", "OBJ//spaceshuttle.obj");

	meshList[GEO_BB8H] = MeshBuilder::GenerateOBJ("bb8head", "OBJ//BB82H.obj");
	meshList[GEO_BB8H]->textureID = LoadTGA("Image//BB82H.tga");

	meshList[GEO_BB8B] = MeshBuilder::GenerateOBJ("bb8body", "OBJ//BB82B.obj");
	meshList[GEO_BB8B]->textureID = LoadTGA("Image//BB82B.tga");

	meshList[GEO_ALIEN] = MeshBuilder::GenerateOBJ("AlienOne", "OBJ//AlienOne.obj");
	meshList[GEO_ALIEN]->textureID = LoadTGA("Image//AlienOne.tga");

	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("table", "OBJ//Table.obj");
	meshList[GEO_TABLE]->textureID = LoadTGA("Image//Table.tga");

	meshList[GEO_CHAIR] = MeshBuilder::GenerateOBJ("chair", "OBJ//Chair.obj");
	meshList[GEO_CHAIR]->textureID = LoadTGA("Image//Chair.tga");

	meshList[GEO_BOX] = MeshBuilder::GenerateOBJ("boxes", "OBJ//Box.obj");
	meshList[GEO_BOX]->textureID = LoadTGA("Image//Box.tga");


	meshList[GEO_DOOR] = MeshBuilder::GenerateCube("door",Color(1,1,1));
	/*<---NPC--->*/

	meshList[GEO_HELMETUI] = MeshBuilder::GenerateQuad("helmetfps", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_HELMETUI]->textureID = LoadTGA("Image//HelmetInside.tga");

	meshList[GEO_TELEPORTER] = MeshBuilder::GenerateOBJ("npc1", "OBJ//Teleporter.obj");
	meshList[GEO_TELEPORTER]->textureID = LoadTGA("Image//Teleporter.tga");

	b_enabletps = false;
	b_tpsDebounce = false;
	tpsTimer = 0;
	gameComplete = false;

	//player = Player(100);


	station = Buildings("spaceshuttle", 10, 0, Vector3(0, -110, 100));

	//furniture
	box1 = Buildings("box 1", 20, 0, Vector3(375, -30, 275));
	collisionVec.push_back(&box1);
	box2 = Buildings("box 2", 20, 0, Vector3(375, -30, 250));
	collisionVec.push_back(&box2);
	box3 = Buildings("box 3", 20, 0, Vector3(375, -30, 225));
	collisionVec.push_back(&box3);
	box4 = Buildings("box 4", 20, 0, Vector3(400, -30, 225));
	collisionVec.push_back(&box4);
	table1 = Buildings("table1", 50, 90, Vector3(-300, -30, 200));
	collisionVec.push_back(&table1);
	chair1 = Buildings("chair1", 20, 0, Vector3(-300, -30, 150));
	collisionVec.push_back(&chair1);

	door = Buildings("door", 0, 0, Vector3(0, 50, -400));

	/*<---Set the position of the NPC--->*/
	b_isWorn = false;
	b_isDisplayUI = false;
	rotateHelm = 0;
	scaleHelm = 50;

	mike1 = Alien("mike1", 30, 0, Vector3(400, -30, 250));
	collisionVec.push_back(&mike1);

	mike2 = Alien("mike2", 30, 90, Vector3(-50, -10, 300));
	mike2.ReadFromTxt("text//SpaceRaceQuestInfo.txt");
	collisionVec.push_back(&mike2);

	mike3 = Alien("mike3", 30, 90, Vector3(175, -10, 300));
	mike3.ReadFromTxt("text//PlatformerQuestInfo.txt");
	collisionVec.push_back(&mike3);

	BB8_ = BB8("BB8", 45, 0, Vector3(250, 10, 50));
	collisionVec.push_back(&BB8_);

	player.setQuest();

	whale = Human("NPCLEPUSMAG", 10, 0, Vector3(75, -20, -300));
	whale.ReadFromTxt("text//keycardQuestDialogue.txt");
	collisionVec.push_back(&whale);

	scene3Tp = Buildings("Scene 3 teleporter", 25, 0, Vector3(300, -30, -250));
	raceTp = Buildings("Scene race teleporter", 25, 0, Vector3(-300, -30, -250));

}
/******************************************************************************/
/*!
\brief
update the scene
*/
/******************************************************************************/
void Sp2_Scene1::Update(double dt)

{
	//camera.Update(dt);
	//camera2.tpsUpdate(camera, dt);
	if (Application::IsKeyPressed('1'))
	{
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('2'))
	{
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('3'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (Application::IsKeyPressed('4'))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (!Application::IsKeyPressed(VK_MENU))
	{
		player.movementUpdate(camera, dt,collisionVec);
		ShowCursor(FALSE);
	}
	
	if (Application::IsKeyPressed(VK_MENU))
	{
		ShowCursor(TRUE);
	}

	fps = std::to_string(1 / dt);

	//npc chat updates
	whale.chat_update(player.pos);
	if (whale.b_dialogueEnd == true)
	{
		if (player.completedMainQuest() == true)
		{
			if (door.pos.x < 150)
			door.pos.x += 20 * dt;
			else if (door.pos.x >= 150)
			{
				gameComplete = true;
			}
		}
		else
		{
			door.pos.x = 0;
		}
	}

	mike2.chat_update(player.pos);

	mike3.chat_update(player.pos);
	if (mike3.b_dialogueEnd == true)
	{
		player.questList[1]->taskComplete(0);
	}
	
	BB8_.moveCircles(dt);
	//BB8_.rotateAbout(dt);


	if (collisionXZ(player.pos, raceTp) == true && Application::IsKeyPressed('E'))
	{
		player.pos = Vector3(-250, 0, -250);
		Application::switchToScene2();
		Application::playSound(2, false);
	}
	if (collisionXZ(player.pos,scene3Tp)==true && Application::IsKeyPressed('E'))
	{
		player.pos = Vector3(250,0,-250);
		Application::switchToScene3();
		Application::playSound(2, false);
	}
	
} 
/******************************************************************************/
/*!
\brief
resetting all variables in the scene
*/
/******************************************************************************/
void Sp2_Scene1::Reset()
{
	b_enabletps = false;
	b_tpsDebounce = false;
	tpsTimer = 0;
	gameComplete = false;

	player = Player();

	station = Buildings("spaceshuttle", 10, 0, Vector3(0, -110, 100));

	//furniture
	box1 = Buildings("box 1", 20, 0, Vector3(375, -30, 275));
	collisionVec.push_back(&box1);
	box2 = Buildings("box 2", 20, 0, Vector3(375, -30, 250));
	collisionVec.push_back(&box2);
	box3 = Buildings("box 3", 20, 0, Vector3(375, -30, 225));
	collisionVec.push_back(&box3);
	box4 = Buildings("box 4", 20, 0, Vector3(400, -30, 225));
	collisionVec.push_back(&box4);
	table1 = Buildings("table1", 50, 90, Vector3(-300, -30, 200));
	collisionVec.push_back(&table1);
	chair1 = Buildings("chair1", 20, 0, Vector3(-300, -30, 150));
	collisionVec.push_back(&chair1);

	door = Buildings("door", 0, 0, Vector3(0, 50, -400));

	/*<---Set the position of the NPC--->*/
	b_isWorn = false;
	b_isDisplayUI = false;
	rotateHelm = 0;
	scaleHelm = 50;

	mike1 = Alien("mike1", 30, 0, Vector3(400, -30, 250));
	collisionVec.push_back(&mike1);

	mike2 = Alien("mike2", 30, 90, Vector3(-50, -10, 300));
	mike2.ReadFromTxt("text//SpaceRaceQuestInfo.txt");
	collisionVec.push_back(&mike2);

	mike3 = Alien("mike3", 30, 90, Vector3(175, -10, 300));
	mike3.ReadFromTxt("text//PlatformerQuestInfo.txt");
	collisionVec.push_back(&mike3);

	BB8_ = BB8("BB8", 45, 0, Vector3(250, 10, 50));
	collisionVec.push_back(&BB8_);

	player.questList.clear();
	player.setQuest();

	whale = Human("NPCLEPUSMAG", 10, 0, Vector3(75, -20, -300));
	whale.ReadFromTxt("text//keycardQuestDialogue.txt");
	collisionVec.push_back(&whale);

	scene3Tp = Buildings("Scene 3 teleporter", 25, 0, Vector3(300, -30, -250));
	raceTp = Buildings("Scene race teleporter", 25, 0, Vector3(-300, -30, -250));
}

void Sp2_Scene1::RenderMesh(Mesh* mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() *	modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
/******************************************************************************/
/*!
\brief
rendering of the skybox
*/
/******************************************************************************/

void Sp2_Scene1::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -10, 0);

	modelStack.PushMatrix();
	modelStack.Translate(0, -25, 0);
	modelStack.Translate(20, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(270, 1, 0, 0);
	RenderMesh(meshList[GEO_BOTTOM], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Translate(camera.position.x, 0, camera.position.z);
	modelStack.Translate(0, 999, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(270, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Translate(camera.position.x, 0, camera.position.z);
	modelStack.Translate(999, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Translate(camera.position.x, 0, camera.position.z);
	modelStack.Translate(-999, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	//modelStack.Translate(camera.position.x, 0, camera.position.z);
	modelStack.Translate(0, 0, -999);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Translate(camera.position.x, 0, camera.position.z);
	modelStack.Translate(0, 0, 999);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

/******************************************************************************/
/*!
\brief
helper render function to render a game object in thhe scene
\param
the game object
\param mesh
the mesh to be render relative to the position and rotation angle of the object
\param enableLight
light enabled or not
\param hasIteractions
whether the game object has interactions to it
\param scale
a vector that handles the scaling of the object rendered
\rotate
a vector that handles the rotation of the object rendered
*/
/******************************************************************************/

void Sp2_Scene1::RenderGameObj(GameObject x, Mesh* mesh, bool enableLight, bool hasInteractions, Vector3 scale, smaller axis)
{
	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x, x.pos.y, x.pos.z);
	//modelStack.Rotate(x.viewAngle, 0, 1, 0);
		modelStack.Rotate(x.viewAngle, 0, 1, 0);
	//modelStack.Rotate(0, 0, 0, 0);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderMesh(mesh, enableLight);
	modelStack.PopMatrix();

	if (hasInteractions == true)
	{
		if (collision(x.pos, camera.position, (x.boundary + 15)))
		{
			modelStack.PushMatrix();
			modelStack.Translate(2, 6, 0);
			RenderTextOnScreen(meshList[GEO_TEXT], "Hold 'E' To Interact", Color(1, 0, 0), 3, 1, 8);
			modelStack.PopMatrix();
		}
	}
}

/******************************************************************************/
/*!
\brief
to render the teleporter as well as a text above it
\param x
the gameobject variable of the teleporter
\param mesh
mesh to be rendered
\param text
the text to be rendered above the teleporter
\param scale
to scale the object
*/
/******************************************************************************/

void Sp2_Scene1::RenderTeleporter(GameObject x, Mesh* mesh, string text, Vector3 scale)
{
	RenderGameObj(x, mesh, true, false, scale);
	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x, x.pos.y, x.pos.z);
	modelStack.Translate(0, 30, 0);
	modelStack.Scale(7, 7, 7);
	RenderText(meshList[GEO_TEXT], text, Color(0, 1, 0));
	modelStack.PopMatrix();

	if (collisionXZ(player.pos,x))
	{
		modelStack.PushMatrix();
		modelStack.Translate(2, 6, 0);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press E to teleport", Color(1, 0, 0), 3, 1, 8);
		modelStack.PopMatrix();
	}
}
/******************************************************************************/
/*!
\brief
to render game character and their lines of dialgue
\param x
game character
\param mesh
mesh to be rendered
\param enableLight
whether light is enabled
\param hasIteractions
whether the object has interactions
\param scale
to scale the object
\param rotate
to rotate the object
*/
/******************************************************************************/
void Sp2_Scene1::RenderGameChar(GameChar x, Mesh* mesh, bool enableLight, bool hasInteractions, Vector3 scale)
{
	RenderGameObj(x, mesh, enableLight, hasInteractions, scale);

	if (x.vec_dialog.empty() == false)
	{
		if (collision(x.pos, player.pos, (x.boundary + player.boundary + x.chat_boundary)) && x.isPressed == true)
		{
			//if (x.dialogue_index == x.vec_dialog.size() - 1 && x.quest!=nullptr)
			//{
			//	player.receiveQuest(x);
			//}
			RenderTextOnScreen(meshList[GEO_TEXT], x.vec_dialog[x.dialogue_index], Color(0, 1, 0), 2, 1, 20);
		}
	}
}

/******************************************************************************/
/*!
\brief
rendering of BB8
*/
/******************************************************************************/
void Sp2_Scene1::RenderBB8(BB8 x)
{
	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x, x.pos.y, x.pos.z);
	modelStack.Rotate(x.viewAngle, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0, -33, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_BB8H], true);	// True false rfers to on/off light respectively

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -34, 0);
	//modelStack.Rotate(x.lowerBodyRotate, 0,0,1);
	modelStack.Rotate(x.viewAngle, 0, 0, -1);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_BB8B], true);

	modelStack.PopMatrix();

	modelStack.PopMatrix();
}


void Sp2_Scene1::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);

}


void Sp2_Scene1::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	//modelStack.PushMatrix();
	//modelStack.Scale(50, 2, 1);
	//RenderMesh(meshList[GEO_TEXTBACKGROUND], false);
	//modelStack.PopMatrix();

	//if (b_isDisplayUI == false || (mesh == meshList[GEO_TEXT]))
	//{
	//    modelStack.Scale(50, 2, 1);
	//    RenderMesh(meshList[GEO_TEXTBACKGROUND], false);
	//}

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();


	glEnable(GL_DEPTH_TEST);
}
/******************************************************************************/
/*!
\brief
rendering a mesh that is tied to the screen
\param mesh
mesh to be rendered
\param translate
translation on the screen
\param scale
to scale the object
\param rotate
to rotate the object
*/
/******************************************************************************/
void Sp2_Scene1::RenderMeshOnScreen(Mesh* mesh, Vector3 translate, Vector3 scale, Vector3 rotate)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -100, 100); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);

	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(translate.x, translate.y, 10);
	modelStack.Rotate(rotate.x, 1, 0, 0);
	modelStack.Rotate(rotate.y, 0, 1, 0);
	modelStack.Rotate(rotate.z, 0, 0, 1);
	modelStack.Scale(scale.x, scale.y, scale.z);

	RenderMesh(mesh, false);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

/******************************************************************************/
/*!
\brief
rendering of the scene for first person camera
*/
/******************************************************************************/
void Sp2_Scene1::Renderfps()
{
	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top()* light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}


	RenderSkybox();

	RenderGameObj(station, meshList[GEO_STATION], true, false, Vector3(2.5, 7, 4));
	RenderGameObj(box1, meshList[GEO_BOX], true, false, Vector3(20, 30, 20));
	RenderGameObj(box2, meshList[GEO_BOX], true, false, Vector3(20, 30, 20));
	RenderGameObj(box3, meshList[GEO_BOX], true, false, Vector3(20, 30, 20));
	RenderGameObj(box4, meshList[GEO_BOX], true, false, Vector3(20, 30, 20));
	RenderGameObj(table1, meshList[GEO_TABLE], true, false, Vector3(30, 40, 30));
	RenderGameObj(chair1, meshList[GEO_CHAIR], true, false, Vector3(10, 12, 10));

	RenderGameObj(door, meshList[GEO_DOOR], true, false, Vector3(150,180,10));
	/*<---NPC--->*/

	//RenderPingu();
	RenderBB8(BB8_);

	RenderGameChar(mike1, meshList[GEO_MIKE], true, true, Vector3(5, 5, 5));
	RenderGameChar(whale, meshList[GEO_NPCLEPUSMAG], true, true, Vector3(10, 10, 10));
	RenderGameChar(mike2, meshList[GEO_ALIEN], true, true, Vector3(12,24,12));
	
	modelStack.PushMatrix();
	modelStack.Translate(mike2.pos.x-5, mike2.pos.y + 40, mike2.pos.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(3,3,3);
	RenderText(meshList[GEO_TEXT],"Space Race quest info",Color(0,1,0));
	modelStack.PopMatrix();

	RenderGameChar(mike3, meshList[GEO_ALIEN], true, true, Vector3(10,24,10));

	modelStack.PushMatrix();
	modelStack.Translate(mike3.pos.x - 5, mike3.pos.y + 40, mike3.pos.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(3, 3, 3);
	RenderText(meshList[GEO_TEXT], "Platformer quest info", Color(0, 1, 0));
	modelStack.PopMatrix();

	RenderTeleporter(scene3Tp, meshList[GEO_TELEPORTER], "To Scene 3", Vector3(15,10,15));
	RenderTeleporter(raceTp, meshList[GEO_TELEPORTER], "To racing Scene", Vector3(15, 10, 15));

	if (gameComplete == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Game Complete", Color(0, 1, 0), 3, 1, 10);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'R' to reset", Color(0, 1, 0), 3, 1, 9);
	}

	RenderMesh(meshList[GEO_AXES], false);
	/*<---Weapons--->*/
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:", Color(0, 1, 0), 3, 13, 18);
	RenderTextOnScreen(meshList[GEO_TEXT], fps, Color(0, 1, 0), 3, 17, 18);
}

void Sp2_Scene1::Rendertps()
{
	RenderSkybox();
	RenderMesh(meshList[GEO_AXES], false);
}

void Sp2_Scene1::Render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	//glViewport(0, 0, screenWidth*2/3, screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
	Mtx44 projection;
	projection.SetToPerspective(45.0f, glfwGetVideoMode(glfwGetPrimaryMonitor())->width / glfwGetVideoMode(glfwGetPrimaryMonitor())->height, 0.1f, 10000.0f);

	projectionStack.LoadMatrix(projection);

	//set View position to camera
	viewStack.LoadIdentity();
	
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	
	modelStack.LoadIdentity();
	Renderfps();
}



void Sp2_Scene1::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}