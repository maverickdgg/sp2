#include "Sp2_Scene3.h"
#include "Human.h"
#include "Alien.h"
#include "BB-8.h"
#include "BB-8_2.h"
#include "Pingu.h"
#include "GL\glew.h"
#include "Buildings.h"
#include "Sir.h"
#include "Platform.h"

#include "shader.hpp"
#include "LoadTGA.h"
#include "Collision.h"
#include "Application.h"

extern GLFWwindow* m_window;

Sp2_Scene3::Sp2_Scene3()
{
}

Sp2_Scene3::~Sp2_Scene3()
{
}

void Sp2_Scene3::Init()
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
	/*frpc = SpaceVehicles("fourth", 5, 30, Vector3(55, 0, 60));
	collisionVec.push_back(&frpc);*/
	camera.Init(Vector3(0, 0, 0), Vector3(10, 0, 0), Vector3(0, 1, 0), 450, 300);
	//camera2.Init(Vector3(50, 20, 50), Vector3(0, 1, 0), frpc.pos);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("AXES", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f, 1.f);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//purplenebula_ft.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//moonSurface.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//purplenebula_bk.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//purplenebula_up.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//purplenebula_rt.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//purplenebula_lf.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("LIGHTBALL", Color(1, 0, 1));

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT2] = MeshBuilder::GenerateText("text2", 16, 16);
	meshList[GEO_TEXT2]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_TEXTBACKGROUND] = MeshBuilder::GenerateQuad("quad", Color(0, 0, 1), 1.f, 1.f);

	meshList[GEO_CHESTBURSTER] = MeshBuilder::GenerateOBJ("chestburster", "OBJ//Chestburster.obj");
	meshList[GEO_CHESTBURSTER]->textureID = LoadTGA("Image//Chestburster_texture.tga");

	meshList[GEO_NECROMANCER] = MeshBuilder::GenerateOBJ("necromancer", "OBJ//Necromancer.obj");
	meshList[GEO_NECROMANCER]->textureID = LoadTGA("Image//Necromancer.tga");

	meshList[GEO_BOX] = MeshBuilder::GenerateOBJ("boxes", "OBJ//Box.obj");
	meshList[GEO_BOX]->textureID = LoadTGA("Image//Box.tga");

	meshList[GEO_HELM] = MeshBuilder::GenerateOBJ("helmet", "OBJ//helmet.obj");
	meshList[GEO_HELM]->textureID = LoadTGA("Image//helmet.tga");
	/*<---NPC--->*/
	meshList[GEO_SUIT] = MeshBuilder::GenerateOBJ("suit", "OBJ//astronautsuit.obj");
	meshList[GEO_SUIT]->textureID = LoadTGA("Image//0001_npcmastronautworker_c.tg4d.tga");

	meshList[GEO_HELMETUI] = MeshBuilder::GenerateQuad("helmetfps", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_HELMETUI]->textureID = LoadTGA("Image//HelmetInside.tga");

	meshList[GEO_DEATHSCREEN] = MeshBuilder::GenerateQuad("death", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_DEATHSCREEN]->textureID = LoadTGA("Image//Blood.tga");

	meshList[GEO_GUIDEHELM] = MeshBuilder::GenerateOBJ("npcsuithelmet", "OBJ//Space_suit_head.obj");
	meshList[GEO_GUIDEHELM]->textureID = LoadTGA("Image//Space_suit_texture.tga");

	meshList[GEO_GUIDEBODY] = MeshBuilder::GenerateOBJ("npcsuit", "OBJ//Space_suit.obj");
	meshList[GEO_GUIDEBODY]->textureID = LoadTGA("Image//Space_suit_texture.tga");

	meshList[GEO_GUIDEARMLEFT] = MeshBuilder::GenerateOBJ("npcsuitleftarm", "OBJ//Space_suit_arm.obj");
	meshList[GEO_GUIDEARMLEFT]->textureID = LoadTGA("Image//Space_suit_texture.tga");

	meshList[GEO_GUIDEARMRIGHT] = MeshBuilder::GenerateOBJ("npcsuitrightarm", "OBJ//Space_suit_arm_right.obj");
	meshList[GEO_GUIDEARMRIGHT]->textureID = LoadTGA("Image//Space_suit_texture.tga");

	meshList[GEO_LADDER] = MeshBuilder::GenerateOBJ("ladder", "OBJ//ladder.obj");
	//meshList[GEO_LADDER]->textureID = LoadTGA("Image//Space_suit_texture.tga");

	meshList[GEO_MEDICBODY] = MeshBuilder::GenerateOBJ("medic", "OBJ//MedicBody.obj");
	meshList[GEO_MEDICBODY]->textureID = LoadTGA("Image//MedicBody.tga");

	meshList[GEO_MEDICARM1] = MeshBuilder::GenerateOBJ("medic", "OBJ//MedicArm1.obj");
	meshList[GEO_MEDICARM1]->textureID = LoadTGA("Image//MedicBody.tga");

	meshList[GEO_MEDICARM2] = MeshBuilder::GenerateOBJ("medic", "OBJ//MedicArm2.obj");
	meshList[GEO_MEDICARM2]->textureID = LoadTGA("Image//MedicBody.tga");

	meshList[GEO_MEDICHEAD] = MeshBuilder::GenerateOBJ("medic", "OBJ//MedicHead.obj");
	meshList[GEO_MEDICHEAD]->textureID = LoadTGA("Image//MedicBody.tga");

	///*<---Under Construction--->*/

	/*<------Platform------>*/
	meshList[GEO_PLATFORM] = MeshBuilder::GenerateOBJ("platform", "OBJ//Platform.obj");
	meshList[GEO_PLATFORM]->textureID = LoadTGA("Image//Platform.tga");

	/**/
	meshList[GEO_BB8v2H] = MeshBuilder::GenerateOBJ("bb8v2head", "OBJ//BB82H.obj");
	meshList[GEO_BB8v2H]->textureID = LoadTGA("Image//BB82H.tga");
	/*<------BB-8 Version 2------>*/
	meshList[GEO_BB8v2B] = MeshBuilder::GenerateOBJ("bb8v2body", "OBJ//BB82B.obj");
	meshList[GEO_BB8v2B]->textureID = LoadTGA("Image//BB82B.tga");

	meshList[GEO_TELEPORTER] = MeshBuilder::GenerateOBJ("npc1", "OBJ//Teleporter.obj");
	meshList[GEO_TELEPORTER]->textureID = LoadTGA("Image//Teleporter.tga");

    meshList[GEO_ROCKET] = MeshBuilder::GenerateOBJ("rocket", "OBJ//Rocket.obj");
    meshList[GEO_ROCKET]->textureID = LoadTGA("Image//Shuttle.tga");

	meshList[GEO_ARROW] = MeshBuilder::GenerateOBJ("arrow", "OBJ//Arrow.obj");
	meshList[GEO_ARROW]->textureID = LoadTGA("Image//Arrow.tga");
	/**/

	b_enabletps = false;
	b_tpsDebounce = false;
	tpsTimer = 0;

	//player = Player(100);

	//furniture
	box1 = Buildings("box 1", 1, 0, Vector3(50, 222.5, -130));
	collisionVec.push_back(&box1);
    box2 = Buildings("box 2", 1, 0, Vector3(-25, 95, -130));
	collisionVec.push_back(&box2);
	box3 = Buildings("box 3", 1, 0, Vector3(375, -30, 225));
	collisionVec.push_back(&box3);
	box4 = Buildings("box 4", 25, 0, Vector3(400, -30, 225));
	collisionVec.push_back(&box4);
	spaceHelm = Human("spacehelm", 10, 30, camera.position);
	/*<---Set the position of the NPC--->*/
	b_isWorn = false;
	b_isDisplayUI = false;
	b_isClimb == false;
	b_isClimb2 = false;
	b_isClimb3 = false;
	b_isClimb4 = false;
    b_isClimb6 = false;
	rotateHelm = 0;
	scaleHelm = 50;

	suit = Human("spacesuit", 5, 0, Vector3(150, 0, 130));
	collisionVec.push_back(&suit);

	ladder = Buildings("ladder1", 1, 0, Vector3(-100, 10, -152.5));
	collisionVec.push_back(&ladder);

	ladder2 = Buildings("ladder2", 1, 270, Vector3(-15, 86, -120));
	collisionVec.push_back(&ladder2);

	ladder3 = Buildings("ladder3", 1, 270, Vector3(-50, 152, -53.5));
	collisionVec.push_back(&ladder3);

	ladder4 = Buildings("ladder4", 1, 140, Vector3(50, 210, -90));
	collisionVec.push_back(&ladder4);

	ChestBurster = AlienEnemy("ChestBurster", 5, 0, Vector3(-50, 125, -125));
	collisionVec.push_back(&ChestBurster);


	Necromancer = AlienEnemy("Necromancer", 5, 0, Vector3(-30, 220, -20));
	collisionVec.push_back(&Necromancer);

	ChestBurster1 = AlienEnemy("ChestBurster1", 5, 0, Vector3(75, 251, -125));
	collisionVec.push_back(&ChestBurster1);

    rocket = Buildings("rocket", 20, 180, Vector3(0, 100, 200));
	collisionVec.push_back(&rocket);

	Arrow = Buildings("arrow", 10, 180, Vector3(70, 30, 30));
	collisionVec.push_back(&Arrow);

	Sir_ = Sir("Sir", 5, 0, Vector3(30, 0, 70));
	Sir_.ReadFromTxt("text//sir.txt");
	collisionVec.push_back(&Sir_);

	Medic_ = Medic("medic", 5, 0, Vector3(-65, 190, -20));
	collisionVec.push_back(&Medic_);

	/**/
	BB8v2_ = BB8v2("BB8v2", 5, 0, Vector3(150, 10, 200));
	BB8v2_.ReadFromTxt("text//bb8v2.txt");
	collisionVec.push_back(&BB8v2_);
	/**/

	/**/
	Platform_ = Platform("platform", 30, 0, Vector3(-80, 8.15, -120));		// Done
	collisionVec.push_back(&Platform_);

	Platform1 = Platform("platform1", 30, 0, Vector3(50, 25, -120));		// Done
	collisionVec.push_back(&Platform1);

	Platform2 = Platform("platform2", 30, 0, Vector3(-50, 150, -25));		// Done
	collisionVec.push_back(&Platform2);

	Platform3 = Platform("platform3", 30, 0, Vector3(-50, 85, -120));		// Done
	collisionVec.push_back(&Platform3);

	Platform4 = Platform("platform4", 30, 0, Vector3(-10, 150, -25));		// Done
	collisionVec.push_back(&Platform4);

	Platform5 = Platform("platform5", 30, 0, Vector3(75, 210, -120));		// To Be Continued...
	collisionVec.push_back(&Platform5);

	Platform6 = Platform("platform6", 10, 0, Vector3(150, 210, -170));
	collisionVec.push_back(&Platform6);

	Platform7 = Platform("platform7", 30, 0, Vector3(420, 408.15, -120));
	collisionVec.push_back(&Platform7);

	Platform8 = Platform("platform8", 30, 0, Vector3(20, 608.15, -120));
	collisionVec.push_back(&Platform8);

	Platform9 = Platform("platform9", 30, 0, Vector3(420, 608.15, -120));
	collisionVec.push_back(&Platform9);

	Platform10 = Platform("platform10", 30, 0, Vector3(220, 808.15, -120));
	collisionVec.push_back(&Platform10);

	spaceStationTp = Buildings("Space station teleporter", 25, 0, Vector3(-200,-30,200));

	player.oxygen = 6000;
    horiDist = 50;
	verticalDistance = 50;
    b_switchDir = false;
    b_collectBox1 = false;
    b_collectBox2 = false;
    b_collectBox3 = false;
}
void Sp2_Scene3::Update(double dt)
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
		if (frpc.b_isInVehicle == false)
		{
			player.movementUpdate(camera, dt, collisionVec);
			player.gunUpdate(camera, dt);
		}
		if (frpc.b_isInVehicle == true)
		{
			//camera2.tpsUpdateVec(frpc.pos);
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

	BB8v2_.chat_update(player.pos);
	Medic_.chat_update(player.pos);
	Sir_.chat_update(player.pos);
	BB8v2_.rotateAbout(dt);

	if (b_isWorn == true && collision(suit.pos, camera.position, suit.boundary) == false)
	{
		if (rotateHelm <= 180)
			rotateHelm += (float)(30 * dt);
		if (scaleHelm <= 650)
			scaleHelm += (float)(100 * dt);
		else
			b_isDisplayUI = true;
	}

	if (b_isDisplayUI == true && collision(ChestBurster.pos, player.pos, 21))
		player.recieveHealthDamage(1);
	if (b_isDisplayUI == true && collision(ChestBurster1.pos, player.pos, 17))
		player.recieveHealthDamage(1);


	if (b_isDisplayUI == true && collision(Necromancer.pos, player.pos, 21))
		player.recieveHealthDamage(1);

	if (player.isDead() == false)
		oldPos = player.pos;
	else if (player.isDead())
	{
		camera.up.x = camera.up.y;
		player.pos = oldPos;
	}

	if (collision(suit, player.pos, 21) && Application::IsKeyPressed('E'))
		b_isWorn = true;
	
	if (b_isDisplayUI == true && player.oxygen > 0)
	{
		--player.oxygen;
	}
	if (player.oxygen <= 0)
	{
		player.recieveHealthDamage(100);
		player.isDead();
	}

    if (Application::IsKeyPressed('E') && player.isDead())
    {
        player.regainHealth(100);
        player.oxygen = 6000;
    }

	ChestBurster.translateWorm(dt);
	ChestBurster.move(dt);

	Necromancer.translateWorm(dt);
	Necromancer.move(dt);


	ChestBurster1.translateWorm(dt);
	ChestBurster1.move(dt);

	//
	Sir_.Salute(dt);

    if (b_isDisplayUI)
    {
        ladder.climb(b_isClimb, ladder, player);
        ladder2.climb(b_isClimb2, ladder2, player);
        ladder3.climb(b_isClimb3, ladder3, player);
		ladder4.climb(b_isClimb4, ladder4, player);
    }

	if (b_isClimb == true)
	{
		if (Application::IsKeyPressed('W'))
			++player.pos.y;
	}
	if (b_isClimb2 == true)
	{
		if (Application::IsKeyPressed('W'))
			++player.pos.y;
	}
    if (b_isClimb3 == true)
    {
        if (Application::IsKeyPressed('W'))
            ++player.pos.y;
    }
    if (b_isClimb4 == true)
    {
        if (Application::IsKeyPressed('W'))
            ++player.pos.y;
    }
	Platform_.changePlatform(b_isClimb, Platform_, player);
	Platform1.changePlatform(b_isClimb2, Platform1, player);
	Platform2.changePlatform(b_isClimb4, Platform2, player);
	Platform3.changePlatform(b_isClimb3, Platform3, player);
	Platform4.changePlatform(b_isClimb4, Platform4, player);
	Platform5.changePlatform(b_isClimb, Platform5, player);
	Platform6.noLadderPlatform(Platform6, player);
	Platform7.changePlatform(b_isClimb, Platform7, player);
	Platform8.changePlatform(b_isClimb, Platform8, player);
	Platform9.changePlatform(b_isClimb, Platform9, player);
	Platform10.changePlatform(b_isClimb, Platform10, player);
	/*<------------------------Horizontal Distance (Platform4)--------------------------------->*/

    if (b_switchDir == false)

    {
        horiDist -= 5 * (dt);

        if (horiDist < -60)

        {
            b_switchDir = true;
        }
    }

    else if (b_switchDir == true)
    {
        horiDist += 5 * (dt);
        if (horiDist > 50)
        {
            b_switchDir = false;
        }
    }

    ladder4.pos.x = horiDist;
    Platform5.pos.x = horiDist + 25;
    ChestBurster1.pos.x = horiDist + 25;
    box1.pos.x = horiDist;
    //if (collision(Platform5.pos, player.pos, player.boundary + Platform5.boundary + 1))
    //    player.pos.x += horiDist;

	/*<------------------------Vertical Distance (Platform5)----------------------------------->*/

	if (b_switchDir == false)
	{
		verticalDistance -= 5 * (dt);
		if (verticalDistance < -220)
		{
			b_switchDir = true;
		}
	}
	else if (b_switchDir == true)
	{
		verticalDistance += 5 * (dt);
		if (verticalDistance > 210)
		{
			b_switchDir = false;
		}
	}
	/*ladder4.pos.x = horiDist;*/
	Platform6.pos.y = verticalDistance + 175;
    //if (collision(Platform6.pos, player.pos, 26))
    //    player.pos.y += verticalDistance;
	//Necromancer.pos.y = verticalDistance + 25;
	/*<-------------------------------End---------------------------------------------------->*/

    if (collision(box1.pos, player.pos, 17) && b_collectBox1 == false)
    {
        b_collectBox1 = true;
    }
    if (collision(box2.pos, player.pos, 17) && b_collectBox2 == false)
    {
        b_collectBox2 = true;
    }
    if (collision(box3.pos, player.pos, 17) && b_collectBox3 == false)
    {
        b_collectBox3 = true;
    }
	//if (Application::IsKeyPressed('O'))


	if (b_switchDir == false)

	if (collisionXZ(player.pos, spaceStationTp) == true && Application::IsKeyPressed('E'))
	{
	    player.pos -= Vector3(50,0,50);
	    Application::switchToScene1();
	}
	if (Application::IsKeyPressed('E') && (collision(Medic_.pos, player.pos, 21)))
	{
		player.regainHealth(100);
	}

}

void Sp2_Scene3::RenderMesh(Mesh* mesh, bool enableLight)
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


void Sp2_Scene3::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(player.pos.x, 0, player.pos.z);
	modelStack.Translate(0, -10, 0);

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

	modelStack.PushMatrix();
	modelStack.Translate(0, -35, 0);
	modelStack.Translate(20, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	modelStack.Rotate(270, 1, 0, 0);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

void Sp2_Scene3::RenderInstructions(GameObject x, Mesh* mesh, string text, Vector3 scale)
{
	RenderGameObj(x, mesh, true, false, scale);
	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x, x.pos.y, x.pos.z);
	modelStack.Translate(-250, 10, 0);
	modelStack.Scale(10, 10, 10);
	RenderText(meshList[GEO_TEXT], text, Color(0, 1, 1));
	modelStack.PopMatrix();

	//if (collisionXZ(player.pos, x))
	//{
	//	modelStack.PushMatrix();
	//	modelStack.Translate(2, 6, 0);
	//	RenderText(meshList[GEO_TEXT], "Please talk to all of the NPCs before proceeding. ", Color(1, 0, 0));
	//	modelStack.PopMatrix();
	//}
}

void Sp2_Scene3::RenderSuit()
{
	modelStack.PushMatrix();
	modelStack.Translate(suit.pos.x, suit.pos.y - 30, suit.pos.z);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(0.4, 0.4, 0.4);
	RenderMesh(meshList[GEO_SUIT], true);
	modelStack.PopMatrix();

	if (collision(suit.pos, player.pos, 21))
	{
		modelStack.PushMatrix();
		modelStack.Translate(2, 6, 0);
		//modelStack.Rotate(0, 1, 0, 0);
		//modelStack.Scale(20, 20, 20);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to wear HEV suit", Color(1, 1, 0), 3, 1, 8);
		modelStack.PopMatrix();
	}

	if (b_isWorn == true)
	{
		//modelStack.PushMatrix();
		//modelStack.Translate(camera.position.x, camera.position.y - 5, camera.position.z + 50);
		//modelStack.Rotate(180, 0, 1, 0);
		//modelStack.Scale(26, 26, 26);
		////modelStack.PopMatrix();
		//RenderMesh(meshList[GEO_HELM], true);
		//modelStack.PopMatrix();
		RenderMeshOnScreen(meshList[GEO_HELM], Vector3(37.5, 0, -10), Vector3(scaleHelm, scaleHelm, scaleHelm), Vector3(0, rotateHelm, 0));
	}

	if (b_isDisplayUI)
	{
		RenderMeshOnScreen(meshList[GEO_HELMETUI], Vector3(40, 30.5, -10), Vector3(30, 40, 10), Vector3(0, 0, 90));
		if (player.isDead() == false)
		{
			RenderTextOnScreen(meshList[GEO_TEXT2], player.getHealthString(), Color(1, 0, 0), 3, 4.8, 2.75);
			RenderTextOnScreen(meshList[GEO_TEXT2], player.getOxygenString(), Color(0, 1, 0), 3, 12, 2.75);
		}
	}
}

void Sp2_Scene3::RenderGameObj(GameObject x, Mesh* mesh, bool enableLight, bool hasInteractions, Vector3 scale, smaller axis)
{
	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x, x.pos.y, x.pos.z);
	//modelStack.Rotate(x.viewAngle, 0, 1, 0);
	if (axis == 1)
		modelStack.Rotate(x.viewAngle, 1, 0, 0);
	else if (axis == 2)
		modelStack.Rotate(x.viewAngle, 0, 1, 0);
	else if (axis == 0)
		axis = 0;
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

void Sp2_Scene3::RenderGameChar(GameChar x, Mesh* mesh, bool enableLight, bool hasInteractions, Vector3 scale)
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

/*<--------------------Scene 3 BB-8------------------------------------------------------->*/
void Sp2_Scene3::RenderBB8v2(BB8v2 n)
{
	modelStack.PushMatrix();
	modelStack.Translate(n.pos.x, n.pos.y, n.pos.z);
	modelStack.Rotate(n.viewAngle, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0, -33, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_BB8v2H], true);	// True false rfers to on/off light respectively

	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(n.pos.x, n.pos.y - 34, n.pos.z);
	modelStack.Rotate(n.viewAngle, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_BB8v2B], true);

	modelStack.PopMatrix();

	if (collision(n.pos, camera.position, (n.boundary + 30)))
	{
		modelStack.PushMatrix();
		modelStack.Translate(2, 6, 0);
		RenderTextOnScreen(meshList[GEO_TEXT], "Click 'E' To Interact", Color(1, 0, 0), 3, 1, 8);
		modelStack.PopMatrix();
	}

	if (n.vec_dialog.empty() == false)
	{
		if (collision(n.pos, player.pos, (n.boundary + player.boundary + n.chat_boundary)) && n.isPressed == true)
		{
			//if (x.dialogue_index == x.vec_dialog.size() - 1 && x.quest!=nullptr)
			//{
			//	player.receiveQuest(x);
			//}
			RenderTextOnScreen(meshList[GEO_TEXT], n.vec_dialog[n.dialogue_index], Color(0, 1, 0), 2, 1, 20);
		}
	}
}

void Sp2_Scene3::RenderSir(/*Sir n*/)
{
	modelStack.PushMatrix();
	modelStack.Translate(Sir_.pos.x, Sir_.pos.y + 37, Sir_.pos.z);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0, -33, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_GUIDEHELM], true);	// True false rfers to on/off light respectively

	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(Sir_.pos.x, Sir_.pos.y - 30, Sir_.pos.z);
	modelStack.Rotate(0, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_GUIDEBODY], true);

	modelStack.PopMatrix();

	/*<------------------------------------------------------------------------------------------------------------->*/

	modelStack.PushMatrix();
	modelStack.Translate(Sir_.pos.x, Sir_.pos.y - 1, Sir_.pos.z - 4);
	modelStack.Rotate(0/*Sir_.viewAngle*/, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_GUIDEARMRIGHT], true);

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(Sir_.pos.x, Sir_.pos.y - 1, Sir_.pos.z + 4);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(Sir_.viewAngle, -1, 0, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_GUIDEARMLEFT], true);

	modelStack.PopMatrix();

	if (collision(Sir_.pos, camera.position, (Sir_.boundary + 30)))
	{
		modelStack.PushMatrix();
		modelStack.Translate(2, 6, 0);
		RenderTextOnScreen(meshList[GEO_TEXT], "Click 'E' To Interact", Color(1, 0, 0), 3, 1, 8);
		modelStack.PopMatrix();
	}

	if (Sir_.vec_dialog.empty() == false)
	{
		if (collision(Sir_.pos, player.pos, (Sir_.boundary + player.boundary + Sir_.chat_boundary)) && Sir_.isPressed == true)
		{
			//if (x.dialogue_index == x.vec_dialog.size() - 1 && x.quest!=nullptr)
			//{
			//	player.receiveQuest(x);
			//}
			RenderTextOnScreen(meshList[GEO_TEXT], Sir_.vec_dialog[Sir_.dialogue_index], Color(0, 1, 0), 2, 1, 20);
		}
	}
}

void Sp2_Scene3::RenderPlatform(Platform p, bool isRotate)
{
	modelStack.PushMatrix();
	modelStack.Translate(p.pos.x, p.pos.y, p.pos.z);
	modelStack.PushMatrix();
	//modelStack.Translate(0, -33, 0);
	if (isRotate == true)
		modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(20, 20, 5);
	RenderMesh(meshList[GEO_PLATFORM], false);	// True false rfers to on/off light respectively

	modelStack.PopMatrix();

	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(p.pos.x + 200, p.pos.y-50, p.pos.z);
	//modelStack.Rotate(p.viewAngle, 0, 0, 1);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(20, 20, 20);
	//RenderMesh(meshList[GEO_PLATFORM], false);

	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(p.pos.x + 500, p.pos.y, p.pos.z);
	//modelStack.Rotate(p.viewAngle, 0, 0, 1);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(20, 20, 60);
	//RenderMesh(meshList[GEO_PLATFORM], false);

	//modelStack.PopMatrix();
	///**/
	//modelStack.PushMatrix();
	//modelStack.Translate(p.pos.x + 900, p.pos.y + 200, p.pos.z);		// 100
	//modelStack.Rotate(p.viewAngle, 0, 0, 1);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(20, 20, 20);
	//RenderMesh(meshList[GEO_PLATFORM], false);

	//modelStack.PopMatrix();
	///**/
	//modelStack.PushMatrix();
	//modelStack.Translate(p.pos.x + 100, p.pos.y + 200, p.pos.z);			// 100
	//modelStack.Rotate(p.viewAngle, 0, 0, 1);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(20, 20, 30);
	//RenderMesh(meshList[GEO_PLATFORM], false);

	//modelStack.PopMatrix();

	///*<------->*/
	//modelStack.PushMatrix();
	//modelStack.Translate(p.pos.x + 500, p.pos.y + 200, p.pos.z);
	//modelStack.Rotate(p.viewAngle, 0, 0, 1);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(20, 20, 20);
	//RenderMesh(meshList[GEO_PLATFORM], false);

	//modelStack.PopMatrix();
	///*<------->*/

	//modelStack.PushMatrix();
	//modelStack.Translate(p.pos.x - 100, p.pos.y + 400, p.pos.z);			// 200
	//modelStack.Rotate(p.viewAngle, 0, 0, 1);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(20, 20, 30);
	//RenderMesh(meshList[GEO_PLATFORM], false);

	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(p.pos.x + 200, p.pos.y + 400, p.pos.z);		// 200
	//modelStack.Rotate(p.viewAngle, 0, 0, 1);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(20, 20, 20);
	//RenderMesh(meshList[GEO_PLATFORM], false);

	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(p.pos.x + 500, p.pos.y + 400, p.pos.z);		// 200
	//modelStack.Rotate(p.viewAngle, 0, 0, 1);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(20, 20, 20);
	//RenderMesh(meshList[GEO_PLATFORM], false);

	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(p.pos.x + 100, p.pos.y + 600, p.pos.z);		// 400
	//modelStack.Rotate(p.viewAngle, 0, 0, 1);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(20, 20, 30);
	//RenderMesh(meshList[GEO_PLATFORM], false);

	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(p.pos.x + 500, p.pos.y + 600, p.pos.z);		// 400
	//modelStack.Rotate(p.viewAngle, 0, 0, 1);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(20, 20, 30);
	//RenderMesh(meshList[GEO_PLATFORM], false);

	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(p.pos.x + 300, p.pos.y + 800, p.pos.z);		// 700
	//modelStack.Rotate(p.viewAngle, 0, 0, 1);
	//modelStack.Rotate(90, 0, 1, 0);
	//modelStack.Scale(20, 20, 30);
	//RenderMesh(meshList[GEO_PLATFORM], false);

	//modelStack.PopMatrix();

	//if (collision(n.pos, camera.position, (n.boundary + 30)))
	//{
	//	modelStack.PushMatrix();
	//	modelStack.Translate(2, 6, 0);
	//	RenderTextOnScreen(meshList[GEO_TEXT], "Click 'E' To Interact", Color(1, 0, 0), 3, 1, 8);
	//	modelStack.PopMatrix();
	//}

	//if (n.vec_dialog.empty() == false)
	//{
	//	if (collision(n.pos, player.pos, (n.boundary + player.boundary + n.chat_boundary)) && n.isPressed == true)
	//	{
	//		//if (x.dialogue_index == x.vec_dialog.size() - 1 && x.quest!=nullptr)
	//		//{
	//		//	player.receiveQuest(x);
	//		//}
	//		RenderTextOnScreen(meshList[GEO_TEXT], n.vec_dialog[n.dialogue_index], Color(0, 1, 0), 2, 1, 20);
	//	}
	//}
}

void Sp2_Scene3::RenderMedic(Medic x)
{
	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x, x.pos.y - 30, x.pos.z);
	modelStack.Rotate(x.viewAngle, 0, 0, 1);
	modelStack.PushMatrix();
	//modelStack.Translate(0, -33, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.4, 0.4, 0.4);
	RenderMesh(meshList[GEO_MEDICBODY], true);	// True false refers to on/off light respectively

	modelStack.PopMatrix();
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x, x.pos.y + 9, x.pos.z);
	modelStack.Rotate(x.viewAngle, 0, 0, 1);
	modelStack.PushMatrix();
	//modelStack.Translate(0, -33, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.4, 0.4, 0.4);
	RenderMesh(meshList[GEO_MEDICHEAD], true);	// True false refers to on/off light respectively

	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x + 0.5, x.pos.y - 1, x.pos.z + 8);
	modelStack.Rotate(x.viewAngle, 0, 0, 1);
	modelStack.PushMatrix();
	//modelStack.Translate(0, -33, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.4, 0.4, 0.4);
	RenderMesh(meshList[GEO_MEDICARM1], true);	// True false refers to on/off light respectively

	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(x.pos.x + 0.5, x.pos.y - 1.5, x.pos.z - 6);
	modelStack.Rotate(x.viewAngle, 0, 0, 1);
	modelStack.PushMatrix();
	//modelStack.Translate(0, -33, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.4, 0.4, 0.4);
	RenderMesh(meshList[GEO_MEDICARM2], true);	// True false refers to on/off light respectively

	modelStack.PopMatrix();
	modelStack.PopMatrix();

	if (collision(x.pos, player.pos, 21))
	{
		modelStack.PushMatrix();
		modelStack.Translate(2, 6, 0);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press E to heal", Color(1, 0, 0), 3, 1, 8);
		modelStack.PopMatrix();
	}
	//if (x.vec_dialog.empty() == false)
	//{
	//	if (collision(x.pos, player.pos, (x.boundary + player.boundary + x.chat_boundary)) && x.isPressed == true)
	//	{
	//		//if (x.dialogue_index == x.vec_dialog.size() - 1 && x.quest!=nullptr)
	//		//{
	//		//	player.receiveQuest(x);
	//		//}
	//		RenderTextOnScreen(meshList[GEO_TEXT], x.vec_dialog[x.dialogue_index], Color(0, 1, 0), 2, 1, 20);
	//	}
	//}

	/*<>*/
}



void Sp2_Scene3::RenderChestBurster()
{
	modelStack.PushMatrix();
	modelStack.Translate(ChestBurster.pos.x + ChestBurster.wormtranslating, ChestBurster.pos.y - 29.5, ChestBurster.pos.z);
	modelStack.Rotate(ChestBurster.viewAngle, 0, 0, 1);
	modelStack.PushMatrix();
	//modelStack.Translate(0, -33, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(ChestBurster.wormrotating, 0, 1, 0);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[GEO_CHESTBURSTER], true);	// True false rfers to on/off light respectively

	modelStack.PopMatrix();

	modelStack.PopMatrix();

}

void Sp2_Scene3::RenderChestBurster1()
{
	modelStack.PushMatrix();
	modelStack.Translate(ChestBurster1.pos.x + ChestBurster1.wormtranslating, ChestBurster1.pos.y - 29.5, ChestBurster1.pos.z);
	modelStack.Rotate(ChestBurster1.viewAngle, 0, 0, 1);
	modelStack.PushMatrix();
	//modelStack.Translate(0, -33, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(ChestBurster1.wormrotating, 0, 1, 0);
	modelStack.Scale(30, 30, 30);
	RenderMesh(meshList[GEO_CHESTBURSTER], true);	// True false rfers to on/off light respectively

	modelStack.PopMatrix();

	modelStack.PopMatrix();

}

void Sp2_Scene3::RenderNecromancer()
{
	modelStack.PushMatrix();
	modelStack.Translate(Necromancer.pos.x, Necromancer.pos.y - 29.5 + Necromancer.wormtranslating, Necromancer.pos.z);
	//modelStack.Rotate(Necromancer.viewAngle, 0, 0, 1);
	modelStack.PushMatrix();
	//modelStack.Translate(0, -33, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(Necromancer.wormrotating, 0, 1, 0);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[GEO_NECROMANCER], true);	// True false rfers to on/off light respectively

	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void Sp2_Scene3::RenderRocket()
{
    modelStack.PushMatrix();
    modelStack.Translate(rocket.pos.x, rocket.pos.y, rocket.pos.z);
    modelStack.Rotate(90, -1, 0, 0);
    modelStack.Scale(30, 30, 30);
    RenderMesh(meshList[GEO_ROCKET], true);
    modelStack.PopMatrix();
}

void Sp2_Scene3::RenderText(Mesh* mesh, std::string text, Color color)
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


void Sp2_Scene3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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


void Sp2_Scene3::RenderMeshOnScreen(Mesh* mesh, Vector3 translate, Vector3 scale, Vector3 rotate)
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


void Sp2_Scene3::RenderTeleporter(GameObject x, Mesh* mesh, string text, Vector3 scale)
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

void Sp2_Scene3::Renderfps()
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

	RenderSkybox();

    if (b_collectBox1 == false)
	    RenderGameObj(box1, meshList[GEO_BOX], true, false, Vector3(5, 5, 5));
    if (b_collectBox2 == false)
	    RenderGameObj(box2, meshList[GEO_BOX], true, false, Vector3(5, 5, 5));
    if (b_collectBox3 == false)
	    RenderGameObj(box3, meshList[GEO_BOX], true, false, Vector3(5, 5, 5));
	RenderGameObj(box4, meshList[GEO_BOX], true, false, Vector3(20, 30, 20));
	RenderChestBurster();
	RenderChestBurster1();
	RenderGameObj(ladder, meshList[GEO_LADDER], true, false, Vector3(9, 9, 9));
	RenderGameObj(ladder2, meshList[GEO_LADDER], true, false, Vector3(9, 9, 9), 2);
    RenderGameObj(ladder3, meshList[GEO_LADDER], true, false, Vector3(9, 9, 9));
	RenderGameObj(ladder4, meshList[GEO_LADDER], true, false, Vector3(9, 9, 9), 2);
    RenderRocket();

	/*<---NPC--->*/
	//RenderPingu();
	//RenderBB8(BB8_);
	RenderSir();
	RenderBB8v2(BB8v2_);
	RenderMedic(Medic_);
	RenderNecromancer();
	RenderInstructions(Arrow, meshList[GEO_ARROW], "Please talk to all of the NPCs before proceeding. ", Vector3(50, 50, 50));
	/*<---Platform--->*/
	RenderPlatform(Platform_, true);
	RenderPlatform(Platform1, false);
	RenderPlatform(Platform2, false);
	RenderPlatform(Platform3, false);
	RenderPlatform(Platform4, false);
	RenderPlatform(Platform5, false);
	RenderPlatform(Platform6, false);
	RenderPlatform(Platform7, false);
	RenderPlatform(Platform8, false);
	RenderPlatform(Platform9, false);
	RenderPlatform(Platform10, false);

    if (player.isDead() == true)
    {
        RenderMeshOnScreen(meshList[GEO_DEATHSCREEN], Vector3(40, 30.5, -10), Vector3(30, 40, 10), Vector3(0, 0, 90));
        RenderTextOnScreen(meshList[GEO_TEXT], "You have died!", Color(1, 0, 0), 4, 2, 4);
        RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E' to respawn.", Color(0, 1, 0), 4, 0.5, 2.5);
    }



    /*<---PLAYERCOSTUME--->*/
    RenderSuit();

	RenderMesh(meshList[GEO_AXES], false);
	/*<---Weapons--->*/
	//if (b_isWorn == false)
	//RenderMeshOnScreen(meshList[GEO_SNIPERRIFLE], Vector3(75, -15, -10), Vector3(250, 250, 250), Vector3(10, 110, 0));

	for (vector<Bullet>::iterator it = laserRifle.bulletVec.begin(); it != laserRifle.bulletVec.end(); ++it)
	{
		modelStack.PushMatrix();
		modelStack.Translate(it->pos.x, it->pos.y, it->pos.z);
		modelStack.Rotate(it->angleY, 0, 1, 0);
		modelStack.Rotate(it->angleX, 0, 0, 1);
		RenderMesh(meshList[GEO_DART], true);
		modelStack.PopMatrix();
	}

	RenderTeleporter(spaceStationTp, meshList[GEO_TELEPORTER], "To Space Station", Vector3(15, 10, 15));
}

void Sp2_Scene3::Rendertps()
{
	RenderSkybox();
	RenderMesh(meshList[GEO_AXES], false);
}

void Sp2_Scene3::Render()
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



void Sp2_Scene3::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}