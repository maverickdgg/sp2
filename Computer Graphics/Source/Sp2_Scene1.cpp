#include "Sp2_Scene1.h"
#include "Human.h"
#include "Alien.h"
#include "GL\glew.h"

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
}

void Sp2_Scene1::Init()
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
	frpc = SpaceVehicles("fourth", 20, 30, Vector3(55, 0, 60));
	camera.Init(Vector3(0, 0, 0), Vector3(10, 0, 0), Vector3(0, 1, 0), 800);
	camera2.Init(Vector3(50,20, 50), Vector3(0,1,0), frpc.pos);

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

	meshList[GEO_TEXTBACKGROUND] = MeshBuilder::GenerateQuad("quad", Color(0, 0, 11), 1.f, 1.f);
	
	/*<---Studio Project 2 OBJs--->*/
	
	meshList[GEO_NPCLEPUSMAG] = MeshBuilder::GenerateOBJ("NPCLEPUSMAG","OBJ//NPCLEPUSMAG.obj");
	meshList[GEO_NPCLEPUSMAG]->textureID = LoadTGA("Image//NPCLEPUSMAG.tga");

	meshList[GEO_FOURTH] = MeshBuilder::GenerateOBJ("fourthplayercontrolled", "OBJ//FourthPlayerControlled.obj");
	meshList[GEO_FOURTH]->textureID = LoadTGA("Image//FourthPlayerControlled.tga");

    meshList[GEO_SNIPERRIFLE] = MeshBuilder::GenerateOBJ("sniperrifle", "OBJ//SniperRifle.obj");
    meshList[GEO_SNIPERRIFLE]->textureID = LoadTGA("Image//0005_npcmastronautworker_sp.tg4d.tga");

    meshList[GEO_DART] = MeshBuilder::GenerateOBJ("dart", "OBJ//dart.obj");
    meshList[GEO_DART]->textureID = LoadTGA("Image//dart.tga");

    //meshList[GEO_HELM] = MeshBuilder::GenerateOBJ("helmet", "OBJ//MKV.obj");
	/*<---NPC--->*/
	meshList[GEO_SUIT] = MeshBuilder::GenerateOBJ("npc1", "OBJ//astronautsuit.obj");
    meshList[GEO_SUIT]->textureID = LoadTGA("Image//0001_npcmastronautworker_c.tg4d.tga");
	//meshList[GEO_SUIT]->textureID = LoadTGA("Image//0005_npcmastronautworker_sp.tg4d.tga");

	meshList[GEO_DEFAULTNPC] = MeshBuilder::GenerateOBJ("npc1", "OBJ//mike.obj");
	meshList[GEO_DEFAULTNPC]->textureID = LoadTGA("Image//mike.tga");

	meshList[GEO_NPC2] = MeshBuilder::GenerateOBJ("npc2", "OBJ//mike.obj");
	meshList[GEO_NPC2]->textureID = LoadTGA("Image//mike.tga");

	meshList[GEO_NPC3] = MeshBuilder::GenerateOBJ("npc3", "OBJ//Stormtrooper.obj");
	meshList[GEO_NPC3]->textureID = LoadTGA("Image//Stormtrooper.tga");

	//meshList[GEO_STATION] = MeshBuilder::GenerateOBJ("spacestation", "OBJ//spaceshuttle.obj");
	
	//meshList[GEO_SPONGEBOBHAND1] = MeshBuilder::GenerateOBJ("spongebobHand1", "OBJ//spongebobHand1.obj");
	//meshList[GEO_SPONGEBOBHAND1]->textureID = LoadTGA("Image//spongebob.tga");

	//meshList[GEO_SPONGEBOBHAND2] = MeshBuilder::GenerateOBJ("spongebobHand2", "OBJ//spongebobHand2.obj");
	//meshList[GEO_SPONGEBOBHAND2]->textureID = LoadTGA("Image//spongebob.tga");

	//meshList[GEO_SPONGEBOBLEG1] = MeshBuilder::GenerateOBJ("spongebobLeg1", "OBJ//spongebobLeg1.obj");
	//meshList[GEO_SPONGEBOBLEG1]->textureID = LoadTGA("Image//spongebob.tga");

	//meshList[GEO_SPONGEBOBLEG2] = MeshBuilder::GenerateOBJ("spongebobLeg2", "OBJ//spongebobLeg2.obj");
	//meshList[GEO_SPONGEBOBLEG2]->textureID = LoadTGA("Image//spongebob.tga");

	//meshList[GEO_SPONGEBOBBODY] = MeshBuilder::GenerateOBJ("spongebobBody", "OBJ//spongebobBody.obj");
	//meshList[GEO_SPONGEBOBBODY]->textureID = LoadTGA("Image//spongebob.tga");

	meshList[GEO_TRANSFORMER] = MeshBuilder::GenerateOBJ("transformer", "OBJ//transformer.obj");
	meshList[GEO_TRANSFORMER]->textureID = LoadTGA("Image//transformer.tga");

	meshList[GEO_KC] = MeshBuilder::GenerateOBJ("krustycrab", "OBJ//KC.obj");
	meshList[GEO_KC]->textureID = LoadTGA("Image//KC.tga");

	meshList[GEO_BB8H] = MeshBuilder::GenerateOBJ("bb8head", "OBJ//BB8H.obj");
	meshList[GEO_BB8H]->textureID = LoadTGA("Image//BB8H.tga");

	meshList[GEO_BB8B] = MeshBuilder::GenerateOBJ("bb8body", "OBJ//BB8B.obj");
	meshList[GEO_BB8B]->textureID = LoadTGA("Image//BB8B.tga");

	meshList[GEO_PINGU] = MeshBuilder::GenerateOBJ("pingu", "OBJ//Pingu.obj");
	meshList[GEO_PINGU]->textureID = LoadTGA("Image//Pingu.tga");
	
	b_enabletps = false;
	b_tpsDebounce = false;
	tpsTimer = 0;

    laserRifle = Gun("laser rifle", 0, Vector3(camera.position.x,camera.position.y ,camera.position.z));

	whale = Human("NPCLEPUSMAG", 0, 30, Vector3(-200, 0, 200));
	whale.ReadFromTxt("Image//Robotdialogue.txt");

	frpc = SpaceVehicles("fourth", 0, 0, Vector3(55, 0, 60));
	//station = Human("spaceshuttle", 10, 0, Vector3(100, -30, 0));
	suit = Human("spacesuit", 30, 30, Vector3(150, 0, 130));

	/*<---Set the position of the NPC--->*/
	objects[NPC].Message = "Press 'E' to wear HEV suit";
	/*<---Miscellaneous--->*/
	//inData.open("Image//Robotdialogue.txt");
	Timer = 0;
	//isPressed = false;
    b_isWorn = false;

	defaultnpc = Human("npc", 0, 30, Vector3(120, -30, 125));	// Default NPC is here only for the interaction codes and not the butler NPC. Do not delete the default npc function.
	npc2 = Alien("npc2", 0, 45, Vector3(500, 0, 125));	// Mike Wazowski
	npc2.ReadFromTxt("Image//mikechat.txt");

	npc3 = Human("npc3", 0, 30, Vector3(-500, 0, -125));	// Storm Trooper
	npc3.ReadFromTxt("Image//Stormtrooper.txt");

	Timer = 0;

	//spongebobLeg1 = Human("spongebobLeg1", 10, 0, Vector3(-60, -37.1 , 125));
	//spongebobLeg2 = Human("spongebobLeg2", 10, 0, Vector3(-60, -37.1 , 125));
	//spongebobHand1 = Human("spongebobHand1", 10, 0, Vector3(-60, -37.1 , 125));
	//spongebobHand2 = Human("spongebobHand2", 10, 0, Vector3(-60, -37.1 , 125));
	//spongebobBody = Human("spongebobBody", 10, 0, Vector3(-60, -37.1 , 125)); 

	transformer = Alien("transformer", 10, 0, Vector3(-500, -30, -300));
	KC = Alien("krustycrab", 10, 0, Vector3(-400, -30, 200));
	BB8H = Alien("bb8head", 10, 0, Vector3(-50, -30, 125));
	BB8B = Alien("bb8body", 10, 0, Vector3(-50, -30, 125));
	Pingu = Alien("pingu", 10, 0, Vector3(50, -30, -125));
}


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
	if (frpc.b_isInVehicle == false)
	{

		camera.view = (camera.target - camera.position).Normalized();
		camera.right = camera.view.Cross(camera.defaultUp);
		camera.right.y = 0;
		camera.right.Normalize();
		this->camera.up = camera.right.Cross(camera.view).Normalized();
		Vector3 tempPos = camera.position;

		if (Application::IsKeyPressed('W'))
		{
			//cam movement

			Vector3 temp_view = (Vector3(camera.target.x, 0, camera.target.z) - Vector3(camera.position.x, 0, camera.position.z)).Normalized();
			tempPos += temp_view *(float)(camera.movementSpeed * dt);
			//if (collision(tempPos, frpc.allGameObj) == false)
				camera.position = tempPos;
		}
		if (Application::IsKeyPressed('S'))
		{
			//cam movement
			Vector3 temp_view = (Vector3(camera.target.x, 0, camera.target.z) - Vector3(camera.position.x, 0, camera.position.z)).Normalized();
			tempPos -= temp_view *(float)(camera.movementSpeed * dt);
			//if (collision(tempPos, frpc.allGameObj) == false)
				camera.position = tempPos;
		}

		if (Application::IsKeyPressed('A'))
		{
			tempPos -= camera.right * (camera.movementSpeed) * dt;
			//if (collision(tempPos, frpc.allGameObj) == false)
				camera.position = tempPos;
		}

		if (Application::IsKeyPressed('D'))
		{
			tempPos += camera.right * (camera.movementSpeed) * dt;
			//if (collision(tempPos, frpc.allGameObj) == false)
				camera.position = tempPos;
		}

		if (Application::IsKeyPressed(VK_SPACE) && camera.b_jumping == false)
		{
			camera.b_jumpUP = true;
			camera.b_jumping = true;
		}

		if (camera.b_jumpUP == true && camera.b_jumping == true)
		{
			camera.f_jumpSpeed -= camera.f_jumpAcceleration * dt;
			camera.position += Vector3(0, camera.f_jumpSpeed + 13, 0) * (float)dt;
			if (camera.f_jumpSpeed <= 0.0f)
			{
				camera.b_jumpUP = false;
			}
		}

		else if (camera.b_jumpUP == false && camera.b_jumping == true)
		{
			camera.f_jumpSpeed += camera.f_jumpAcceleration * dt;
			camera.position -= Vector3(0, camera.f_jumpSpeed + 13, 0) * (float)dt;
			if (camera.f_jumpSpeed >= 50.0f)
			{
				camera.position.y = 0;
				camera.b_jumpUP = true;
				camera.b_jumping = false;
			}
		}

		if (camera.position.x > camera.boundary)
		{
			camera.position.x = camera.boundary;
		}
		if (camera.position.x < -camera.boundary)
		{
			camera.position.x = -camera.boundary;
		}
		if (camera.position.z > camera.boundary)
		{
			camera.position.z = camera.boundary;
		}
		if (camera.position.z < -camera.boundary)
		{
			camera.position.z = -camera.boundary;
		}
	}
	
	if (!Application::IsKeyPressed(VK_MENU))
	{
		if (frpc.b_isInVehicle == false)
		{
			camera.updateRotation(0.3);
		}
		else if (frpc.b_isInVehicle == true)
		{
			camera2.tpsUpdateVec(frpc.pos);
		}
		ShowCursor(FALSE);
	}

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

	//gun update

    laserRifle.view = camera.view;
	laserRifle.viewAngleX = camera.cameraRotationX;
    laserRifle.viewAngle = camera.cameraRotationY;
	laserRifle.pos = Vector3(camera.position.x, camera.position.y - 5, camera.position.z);

	if (Application::IsKeyPressed(VK_LBUTTON))
	{
		laserRifle.fire(dt);
	}
	laserRifle.updateBullet(dt);


	Timer++;
	if (Timer % 10 == 0)
	{
		RenderSuit();
	}

 /*   if (collision(suit, camera.position, suit.boundary) && Application::IsKeyPressed('E'))
        b_isWorn = true;*/
	if (frpc.b_isInVehicle == true)
	{
		frpc.updateVehicle(Application::IsKeyPressed('W'), Application::IsKeyPressed('S'), Application::IsKeyPressed('A'), Application::IsKeyPressed('D'), dt);
	}

	//npc chat updates
	whale.chat_update(camera.position);
	npc2.chat_update(camera.position);
	npc3.chat_update(camera.position);
	
	frpc.enterVehicleUpdate();
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


void Sp2_Scene1::RenderSkybox(Camera3 camera)
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

void Sp2_Scene1::RenderSuit()
{
    modelStack.PushMatrix();
    modelStack.Translate(suit.pos.x, suit.pos.y - 30, suit.pos.z);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(0.5, 0.5, 0.5);
    RenderMesh(meshList[GEO_SUIT], true);
    // Text for NPC Interaction
    modelStack.PopMatrix();
    if (collision(suit.pos, camera.position, suit.boundary))
    {
        modelStack.PushMatrix();
        modelStack.Translate(2, 6, 0);
        //modelStack.Rotate(0, 1, 0, 0);
        //modelStack.Scale(20, 20, 20);
        RenderTextOnScreen(meshList[GEO_TEXT], objects[NPC].Message, Color(1, 1, 0), 3, 1, 8);
        modelStack.PopMatrix();
    }

    if (b_isWorn == true)
    {
        //modelStack.PushMatrix();
        //modelStack.Scale(10, 10, 10);
        //RenderMesh(meshList[GEO_RIGHTARM], true);
        //modelStack.PopMatrix();
        RenderMeshOnScreen(meshList[GEO_HELM], Vector3(75, -15, -10), Vector3(20, 20, 20), Vector3(0, 0, 0));
    }
}

void Sp2_Scene1::RenderGameObj(GameObject x, Mesh* mesh,bool enableLight,bool hasInteractions,Vector3 scale)
{
	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x, x.pos.y, x.pos.z);
	modelStack.Rotate(x.viewAngle, 0, 1, 0);
	modelStack.Scale(scale.x,scale.y,scale.z);
	RenderMesh(mesh,enableLight);
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

void Sp2_Scene1::RenderGameChar(GameChar x, Mesh* mesh,  bool enableLight, bool hasInteractions, Vector3 scale)
{
	RenderGameObj(x, mesh, enableLight,hasInteractions ,scale);

	if (x.vec_dialog.empty() == false)
	{
		if (collision(x.pos, camera.position, (x.boundary + 15)) && x.isPressed == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], x.vec_dialog[x.dialogue_index], Color(1, 1, 1), 3, 1, 10);
		}

	}
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

	modelStack.PushMatrix();
	modelStack.Scale(50, 2, 1);
	RenderMesh(meshList[GEO_TEXTBACKGROUND], false);
	modelStack.PopMatrix();

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


void Sp2_Scene1::RenderMeshOnScreen(Mesh* mesh, Vector3 translate, Vector3 scale , Vector3 rotate )
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


void Sp2_Scene1::Renderfps()
{
	RenderSkybox(camera);

	RenderGameObj(frpc, meshList[GEO_FOURTH],true,true);  

	/*<---NPC--->*/
	RenderSuit();

	RenderGameChar(defaultnpc, meshList[GEO_DEFAULTNPC],70);
	RenderGameChar(whale, meshList[GEO_NPCLEPUSMAG], 70);
	RenderGameChar(npc2, meshList[GEO_NPC2], 70);
	RenderGameChar(npc3, meshList[GEO_NPC3], 70);
	//RenderGameChar(station, meshList[GEO_STATION], 70);
	//RenderGameChar(spongebobLeg1, meshList[GEO_SPONGEBOBLEG1],70, false ,Vector3(10,10,10));
	//RenderGameChar(spongebobLeg2, meshList[GEO_SPONGEBOBLEG2], 70, false, Vector3(10, 10, 10));
	//RenderGameChar(spongebobHand1, meshList[GEO_SPONGEBOBHAND1], 70, false, Vector3(10, 10, 10));
	//RenderGameChar(spongebobHand2, meshList[GEO_SPONGEBOBHAND2], 70, false, Vector3(10, 10, 10));
	//RenderGameChar(spongebobBody, meshList[GEO_SPONGEBOBBODY], 70, false, Vector3(10, 10, 10));

	RenderGameChar(transformer, meshList[GEO_TRANSFORMER], 70, true, Vector3(10, 10, 10));
	RenderGameChar(KC, meshList[GEO_KC], 70, true, Vector3(50, 50, 50));
	RenderGameChar(BB8H, meshList[GEO_BB8H], 70, true, Vector3(10, 10, 10));
	RenderGameChar(BB8B, meshList[GEO_BB8B], 70, true, Vector3(10, 10, 10));
	RenderGameChar(Pingu, meshList[GEO_PINGU], 70, true, Vector3(10, 10, 10));

	RenderMesh(meshList[GEO_AXES], false); 
	/*<---Weapons--->*/
    if (b_isWorn == false) // b_isInVehicle == false
	    RenderMeshOnScreen(meshList[GEO_SNIPERRIFLE],Vector3(75,-15,-10),Vector3(250,250,250),Vector3(10,110,0));

	for (vector<Bullet>::iterator it = laserRifle.bulletVec.begin(); it != laserRifle.bulletVec.end(); ++it)
	{
		modelStack.PushMatrix();
		modelStack.Translate(it->pos.x, it->pos.y, it->pos.z);
		modelStack.Rotate(it->angleY, 0, 1, 0);
		modelStack.Rotate(it->angleX, 0, 0, 1);
		RenderMesh(meshList[GEO_DART], true);
		modelStack.PopMatrix();
	}
}

void Sp2_Scene1::Rendertps()
{
	RenderSkybox(camera);
	

	RenderMesh(meshList[GEO_AXES], false);


}

void Sp2_Scene1::Render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 projection;


	//glViewport(0, 0, screenWidth*2/3, screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
	projection.SetToPerspective(45.0f, glfwGetVideoMode(glfwGetPrimaryMonitor())->width / glfwGetVideoMode(glfwGetPrimaryMonitor())->height, 0.1f, 10000.0f);


	projectionStack.LoadMatrix(projection);

	viewStack.LoadIdentity();

	//set View position to camera
	if (frpc.b_isInVehicle == true)
	{
		viewStack.LookAt(
		camera2.position.x, camera2.position.y, camera2.position.z,
		camera2.target.x, camera2.target.y, camera2.target.z,
		camera2.up.x, camera2.up.y, camera2.up.z
		);
	}
	
	else if (frpc.b_isInVehicle == false)
	{
		viewStack.LookAt(
			camera.position.x, camera.position.y, camera.position.z,
			camera.target.x, camera.target.y, camera.target.z,
			camera.up.x, camera.up.y, camera.up.z
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



void Sp2_Scene1::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}