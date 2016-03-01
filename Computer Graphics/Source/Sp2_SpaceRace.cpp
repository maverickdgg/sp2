#include "Sp2_SpaceRace.h"
#include "Human.h"
#include "Alien.h"
#include "BB-8.h"
#include "Pingu.h"
#include "GL\glew.h"
#include "Buildings.h"
#include "AlienEnemy.h"
#include "shader.hpp"
#include "LoadTGA.h"
#include "Collision.h"
#include "Application.h"
#include "ChestBurster.h"

extern GLFWwindow* m_window;

Sp2_SpaceRace::Sp2_SpaceRace()
{
}

Sp2_SpaceRace::~Sp2_SpaceRace()
{
}

void Sp2_SpaceRace::Init()
{

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

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_MVP] = glGetUniformLocation(m_programID,
		"MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID,
		"MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] =
		glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] =
		glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] =
		glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] =
		glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] =
		glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] =
		glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] =
		glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] =
		glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	//handler for text
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	light[0].position.Set(0, 20, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

	//make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 5);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	//spot light
	light[0].type = Light::LIGHT_SPOT;
	light[0].position.Set(0, 200, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 30;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1,
		&light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	//geom init
	frpc = SpaceVehicles("frpc", 10, 0, indexToVector(toIndex(44,25)));
	collisionVec.push_back(&frpc);
	camera.Init(Vector3(0, 0, 0), Vector3(10, 0, 0), Vector3(0, 1, 0), 1000, 1000);
	camera2.Init(Vector3(-50, 15, -50), Vector3(0, 1, 0), &frpc);
	camera2.b_cameraLock = true;

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

	meshList[GEO_TEXTBACKGROUND] = MeshBuilder::GenerateQuad("quad", Color(0, 0, 1), 1.f, 1.f);

	/*<---Studio Project 2 OBJs--->*/

	meshList[GEO_NPCLEPUSMAG] = MeshBuilder::GenerateOBJ("NPCLEPUSMAG", "OBJ//NPCLEPUSMAG.obj");
	meshList[GEO_NPCLEPUSMAG]->textureID = LoadTGA("Image//NPCLEPUSMAG.tga");

	meshList[GEO_FOURTH] = MeshBuilder::GenerateOBJ("fourthplayercontrolled", "OBJ//FourthPlayerControlled.obj");
	meshList[GEO_FOURTH]->textureID = LoadTGA("Image//FourthPlayerControlled.tga");
	/*<--- GUN --->*/
	meshList[GEO_SNIPERRIFLE] = MeshBuilder::GenerateOBJ("sniperrifle", "OBJ//SniperRifle.obj");
	meshList[GEO_SNIPERRIFLE]->textureID = LoadTGA("Image//0005_npcmastronautworker_sp.tg4d.tga");

	meshList[GEO_DART] = MeshBuilder::GenerateOBJ("dart", "OBJ//dart.obj");
	meshList[GEO_DART]->textureID = LoadTGA("Image//dart.tga");
	/*<---NPC--->*/
	meshList[GEO_MIKE] = MeshBuilder::GenerateOBJ("npc1", "OBJ//mike.obj");
	meshList[GEO_MIKE]->textureID = LoadTGA("Image//mike.tga");

	meshList[GEO_BOX] = MeshBuilder::GenerateOBJ("boxes", "OBJ//Box.obj");
	meshList[GEO_BOX]->textureID = LoadTGA("Image//Box.tga");

	meshList[GEO_ALIEN] = MeshBuilder::GenerateOBJ("AlienOne", "OBJ//AlienOne.obj");
	meshList[GEO_ALIEN]->textureID = LoadTGA("Image//AlienOne.tga");

	meshList[GEO_TELEPORTER] = MeshBuilder::GenerateOBJ("npc1", "OBJ//Teleporter.obj");
	meshList[GEO_TELEPORTER]->textureID = LoadTGA("Image//Teleporter.tga");

	/*<---NPC--->*/
	b_enabletps = false;
	b_tpsDebounce = false;
	b_raceBegin = false;
	b_raceStart = false;
	b_raceEnd = false;
	f_endTimer = 3;
	tpsTimer = 0;
	f_raceCountdown = 3;

	player = Player(indexToVector(toIndex(11,37)));

	spaceRaceNpc = Alien("Space Race NPC", 20, 0, indexToVector(toIndex(3, 6))+ Vector3(0,-10,0) );
	spaceRaceNpc.ReadFromTxt("text//spaceRaceDialogue.txt");

	racePosition = 2;

	// cpu racers
	frpc2 = SpaceVehicles("frpc2", 10, 0, indexToVector(toIndex(44, 26)) , 110);
	//loading of map;
	racetrack = load_map("text//map1.txt");
	racePath.push(toIndex(44,45));
	racePath.push(toIndex(33,45));
	racePath.push(toIndex(33,42));
	racePath.push(toIndex(29,38));
	racePath.push(toIndex(29,34));
	racePath.push(toIndex(34,34));
	racePath.push(toIndex(34,23));
	racePath.push(toIndex(20,23));
	racePath.push(toIndex(20,14));
	racePath.push(toIndex(28,6));
	racePath.push(toIndex(44,6));

	frpc.racepath = racePath;
	frpc2.racepath = racePath;

	spaceStationtp = Buildings("Space station teleporter", 25, 0, indexToVector(toIndex(10,10)) + Vector3(0,-30,0));
}

void Sp2_SpaceRace::Update(double dt)
{

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
		if (frpc.b_isInVehicle == false)
		{
			player.movementUpdate(camera, dt, collisionVec,racetrack);
		}
		else
		{
			camera2.tpsUpdateVec(dt);
			if (b_raceStart == true)
			{
				frpc.updateVehicle(dt, racetrack,frpc.racepath);
			}
		}

		ShowCursor(FALSE);
	}
	//frpc.enterVehicleUpdate(player);
	if (Application::IsKeyPressed(VK_MENU))
	{
		ShowCursor(TRUE);
	}

	if (Application::IsKeyPressed('M') && b_enabletps == true && b_tpsDebounce == false)
	{
		b_tpsDebounce = true;
		b_enabletps = false;
	}
	if (Application::IsKeyPressed('M') && b_enabletps == false && b_tpsDebounce == false)
	{
		b_tpsDebounce = true;
		b_enabletps = true;
	}
	if (b_tpsDebounce == true)
	{
		tpsTimer += dt;
		if (tpsTimer >= 2)
		{
			b_tpsDebounce = false;
			tpsTimer = 0;
		}
	}
	if (collisionXZ(player.pos, spaceStationtp) == true && Application::IsKeyPressed('E'))
	{
		player.pos = indexToVector(toIndex(12, 12));
		Application::switchToScene1();
	}
	speed = std::to_string(frpc.speed);

	if (b_raceStart == true)
	{
		frpc2.updateCPUVehicle(dt, racetrack, frpc2.racepath);
		racePosition = frpc.getRacePosition(frpc2, toIndex(44, 45));
	}
	

	spaceRaceNpc.chat_update(player.pos);
	if (spaceRaceNpc.b_dialogueEnd == true)
	{
		b_raceBegin = true;
		frpc.b_isInVehicle = true;
		f_raceCountdown = 6.0f;
		player.pos = indexToVector(toIndex(11, 37));

	}
	if (b_raceBegin == true && f_raceCountdown > 0)
	{
		f_raceCountdown -= dt;
	}
	if (f_raceCountdown <= 0)
	{
		f_raceCountdown == 0;
		b_raceStart = true;
		b_raceBegin = false;
	}
	spaceRaceNpc.pulsingUpdate(dt);

	if (frpc.lap >= 3)
	{
		//resetting the race after 3 laps.
		b_raceStart = false;
		b_raceEnd = true;
		f_endTimer = 5.f;
		
		f_raceCountdown = 6.0f;
		frpc.b_isInVehicle = false;
		frpc = SpaceVehicles("frpc", 10, 0, indexToVector(toIndex(44, 25)));
		frpc2 = SpaceVehicles("frpc2", 10, 0, indexToVector(toIndex(44, 26)), 110);	
		frpc2.racepath = racePath;
	}
	if (b_raceEnd == true)
	{
		f_endTimer -= dt;
		if (f_endTimer <= 0)
		{
			frpc.lap = 0;
			frpc2.lap = 0;
			b_raceEnd = false;
		}
	}
}

void Sp2_SpaceRace::RenderMesh(Mesh* mesh, bool enableLight)
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


void Sp2_SpaceRace::RenderSkybox(Camera camera)
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -10, 0);

	modelStack.PushMatrix();
	modelStack.Translate(0, -25, 0);
	modelStack.Translate(20, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(270, 1, 0, 0);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, 0, camera.position.z);
	modelStack.Translate(0, 999, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Rotate(270, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, 0, camera.position.z);
	modelStack.Translate(999, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, 0, camera.position.z);
	modelStack.Translate(-999, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, 0, camera.position.z);
	modelStack.Translate(0, 0, -999);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, 0, camera.position.z);
	modelStack.Translate(0, 0, 999);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}


void Sp2_SpaceRace::RenderGameObj(GameObject x, Mesh* mesh, bool enableLight, bool hasInteractions, Vector3 scale, Vector3 rotate)
{
	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x, x.pos.y, x.pos.z);
	modelStack.Rotate(x.viewAngle, 0, 1, 0);
	modelStack.Rotate(rotate.x, 1, 0, 0);
	modelStack.Rotate(rotate.y, 0, 1, 0);
	modelStack.Rotate(rotate.z, 0, 0, 1);
	
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

void Sp2_SpaceRace::RenderGameObj(Mesh* mesh, Vector3 pos, Vector3 scale, Vector3 rotate)
{
	modelStack.PushMatrix();

	modelStack.Translate(pos.x, pos.y, pos.z);
	modelStack.Rotate(rotate.x, 1, 0, 0);
	modelStack.Rotate(rotate.y, 0, 1, 0);
	modelStack.Rotate(rotate.z, 0, 0, 1);
	modelStack.Scale(scale.x, scale.y, scale.z);
	RenderMesh(mesh, true);

	modelStack.PopMatrix();
}

void Sp2_SpaceRace::RenderGameChar(GameChar x, Mesh* mesh, bool enableLight, bool hasInteractions, Vector3 scale, Vector3 rotate)
{
	RenderGameObj(x, mesh, enableLight, hasInteractions, scale, rotate);
	if (x.vec_dialog.empty() == false)
	{
		if (collision(x.pos, player.pos, (x.boundary + player.boundary + x.chat_boundary)) && x.isPressed == true)
		{

			RenderTextOnScreen(meshList[GEO_TEXT], x.vec_dialog[x.dialogue_index], Color(0, 1, 0), 2, 1, 20);
		}
	}
}

void Sp2_SpaceRace::RenderText(Mesh* mesh, std::string text, Color color)
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


void Sp2_SpaceRace::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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


void Sp2_SpaceRace::RenderMeshOnScreen(Mesh* mesh, Vector3 translate, Vector3 scale, Vector3 rotate)
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

	RenderMesh(mesh, b_lightEnabled);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void Sp2_SpaceRace::RenderTeleporter(GameObject x, Mesh* mesh, string text, Vector3 scale)
{
	RenderGameObj(x, mesh, true, false, scale);
	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x, x.pos.y, x.pos.z);
	modelStack.Translate(0, 30, 0);
	modelStack.Scale(7, 7, 7);
	RenderText(meshList[GEO_TEXT], text, Color(0, 1, 0));
	modelStack.PopMatrix();

	if (collisionXZ(player.pos, x))
	{
		modelStack.PushMatrix();
		modelStack.Translate(2, 6, 0);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press E to teleport", Color(1, 0, 0), 3, 1, 8);
		modelStack.PopMatrix();
	}
}

void Sp2_SpaceRace::Renderfps()
{
	Vector3 lightDir(light[0].position.x,
		light[0].position.y, light[0].position.z);
	Vector3 lightDirection_cameraspace = viewStack.Top() *
		lightDir;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	for (int i = 0; i < 2500; ++i)
	{
		if (racetrack->data[i] == '1')
		{
			RenderGameObj(meshList[GEO_BOX], indexToVector(i) + Vector3(10, -30, 10), Vector3(20, 40, 20), Vector3(0, 0, 0));
		}
	}

	RenderSkybox(camera);

	

	RenderGameObj(frpc, meshList[GEO_FOURTH],false,false,Vector3(0.5,0.5,0.5),Vector3(0,0,frpc.rotationZ));  
	RenderGameObj(frpc2, meshList[GEO_FOURTH], false, false, Vector3(0.5, 0.5, 0.5), Vector3(0, 0, frpc2.rotationZ));


	RenderGameChar(spaceRaceNpc, meshList[GEO_ALIEN], true, false, Vector3(12,24,12)+(Vector3(1,0.6,1) * spaceRaceNpc.f_scaleBig ));
	RenderTeleporter(spaceStationtp, meshList[GEO_TELEPORTER], "To Space Station", Vector3(15, 10, 15));

	if (frpc.b_isInVehicle == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT],speed, Color(0, 1, 0), 3, 1,1);
		RenderTextOnScreen(meshList[GEO_TEXT], "Current Lap :", Color(0, 1, 0), 2, 1, 27);
		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(frpc.lap+1), Color(0, 1, 0), 3, 10, 18);
		RenderTextOnScreen(meshList[GEO_TEXT], "/ 3", Color(0, 1, 0), 3, 11, 18);
		if (racePosition == 1)
			RenderTextOnScreen(meshList[GEO_TEXT], "1st", Color(0, 1, 0), 3, 1, 17);
		else if (racePosition == 2)
			RenderTextOnScreen(meshList[GEO_TEXT], "2nd", Color(0, 1, 0), 3, 1, 17);
	}
	

	if (b_raceBegin == true && f_raceCountdown > 4)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "3", Color(0, 1, 0), 10, 3, 3);
	}
	else if (b_raceBegin == true && f_raceCountdown > 2)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "2", Color(0, 1, 0), 10, 3, 3);
	}
	else if (b_raceBegin == true && f_raceCountdown > 0)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "1", Color(0, 1, 0), 10, 3, 3);
	}

	if (b_raceEnd == true)
	{
		if (racePosition == 1)
			RenderTextOnScreen(meshList[GEO_TEXT], "Congragulations! You WIN!", Color(0, 1, 0), 3, 1, 10);
		else if (racePosition == 2)
			RenderTextOnScreen(meshList[GEO_TEXT], "YOU LOSE! TRY AGAIN!", Color(0, 1, 0), 3, 1, 10);
	}

	RenderMesh(meshList[GEO_AXES], false);


}

void Sp2_SpaceRace::Rendertps()
{
	RenderSkybox(camera);
	RenderMesh(meshList[GEO_AXES], false);
}

void Sp2_SpaceRace::Render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 projection;


	//glViewport(0, 0, screenWidth*2/3, screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
	projection.SetToPerspective(45.0f, glfwGetVideoMode(glfwGetPrimaryMonitor())->width / glfwGetVideoMode(glfwGetPrimaryMonitor())->height, 0.1f, 10000.0f);


	projectionStack.LoadMatrix(projection);

	viewStack.LoadIdentity();

	//set View position to camera
	if (frpc.b_isInVehicle == false)
	{
		viewStack.LookAt(
			camera.position.x, camera.position.y, camera.position.z,
			camera.target.x, camera.target.y, camera.target.z,
			camera.up.x, camera.up.y, camera.up.z
			);
	}
	else if (frpc.b_isInVehicle == true)
	{
		viewStack.LookAt(
			camera2.position.x, camera2.position.y, camera2.position.z,
			camera2.target.x, camera2.target.y, camera2.target.z,
			camera2.up.x, camera2.up.y, camera2.up.z
			);
	}

	Renderfps();

	if (b_enabletps == true)
	{
		glViewport(screenWidth * 2 / 3, screenHeight / 10, screenWidth / 3, screenHeight / 3);

		glClear(GL_DEPTH_BUFFER_BIT);

		projection.SetToPerspective(45.0f, glfwGetVideoMode(glfwGetPrimaryMonitor())->width / glfwGetVideoMode(glfwGetPrimaryMonitor())->height, 0.1f, 10000.0f);
		projectionStack.LoadMatrix(projection);
		viewStack.LoadIdentity();
		//set View position to camera
		viewStack.LookAt(
			camera2.position.x, camera2.position.y, camera2.position.z,
			camera2.target.x, camera2.target.y, camera2.target.z,
			camera2.up.x, camera2.up.y, camera2.up.z
			);
		Rendertps();
	}
}



void Sp2_SpaceRace::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}