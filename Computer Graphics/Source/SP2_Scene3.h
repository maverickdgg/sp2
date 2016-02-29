#ifndef SP2_SCENE3_H
#define SP2_SCENE3_H

#include "Scene.h"
#include"Mtx44.h"
#include "Application.h"
#include "Camera3.h"
#include "CameraTPS.h"
#include"Mesh.h"
#include"MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include"Material.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "GameObject.h"
#include "SpaceVehicles.h"
#include "Buildings.h"

#include "Gun.h"

#include "Human.h"
#include "Alien.h"
#include "AlienEnemy.h"
#include "Player.h"
#include "BB-8.h"
#include "BB-8_2.h"
#include "Pingu.h"
#include "Quest.h"
#include "Sir.h"
#include "Platform.h"
#include "Medic.h"

class Sp2_Scene3 : public Scene
{
public:
	Sp2_Scene3();
	~Sp2_Scene3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum GEOMETRY_TYPE
	{
		/*<---Studio Project 2--->*/
		/*---Essentials---*/
		GEO_AXES,
		GEO_QUAD,
		GEO_LIGHTBALL,
		/*---Scene Skybox---*/
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		/*<---Text--->*/
		GEO_TEXT,
		GEO_TEXT2,
		GEO_TEXTBACKGROUND,
		/*<---Space Vehicles--->*/
		GEO_FOURTH,
		GEO_NPCLEPUSMAG,
		GEO_STATION, // SpaceShuttle
		/*<---Weapons--->*/
		GEO_SNIPERRIFLE,
		GEO_DART,
		GEO_CROSSHAIR,
		/*<---Humans--->*/
		GEO_SUIT,
		GEO_HELM,
		GEO_GUIDEHELM,
		GEO_GUIDEBODY,
		GEO_GUIDEARMLEFT,
		GEO_GUIDEARMRIGHT,

		/*<---NPC--->*/
		GEO_MIKE,	// Default (Pure Interaction Codes, no NPC)	
		GEO_NPC3,	// Storm Trooper
		GEO_FLIGHTUI,	// Astronaut Suit
		GEO_HELMETUI,
		GEO_BB8H,	// BB-8 Head
		GEO_BB8B,	// BB-8 Body
		GEO_BB8v2H,
		GEO_BB8v2B,
		GEO_PINGU,
		GEO_CHESTBURSTER,
		GEO_NECROMANCER,
		GEO_PLATFORM,
		GEO_LADDER,

		GEO_PINGUBODY,
		GEO_PINGULH,
		GEO_PINGURH,

		GEO_BOX,
		GEO_TABLE,
		GEO_CHAIR,
		GEO_KEYCARD,
		GEO_DEATHSCREEN,
		/*<------Medic------>*/
		GEO_MEDICBODY,
		GEO_MEDICHEAD,
		GEO_MEDICARM1,
		GEO_MEDICARM2,

		/*<---Do not touch--->*/
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};

	unsigned m_parameters[U_TOTAL];

	Camera3 camera;
	CameraTPS camera2;

	float LSPEED;
	bool b_lightEnabled;
	int screenWidth, screenHeight;
	Vector3 tempPos;
	bool b_enabletps;
	bool b_tpsDebounce;
	bool b_isWorn;
	bool b_isDisplayUI;
	bool b_isClimb;
	bool b_isClimb2;
    bool b_isClimb3;
	bool b_isClimb4;
    bool b_switchDir;
    float horiDist;
	float rotateHelm;
	float scaleHelm;
	float tpsTimer;
	Vector3 oldPos;

	Gun laserRifle;
	SpaceVehicles np;
	SpaceVehicles frpc;
	Buildings station;
	Alien mike1, mike2, mike3;
	Human whale;
	Human suit;
	Human spaceHelm;
	BB8 BB8_;
	BB8v2 BB8v2_;
	Medic Medic_;
	Pingu Pingu_;
	Quest raceQuest;
	AlienEnemy ChestBurster;

	AlienEnemy Necromancer;

	AlienEnemy ChestBurster1;

	Sir Sir_;
	Platform Platform_;
	Platform Platform1;
	Platform Platform2;
	Platform Platform3;
	Platform Platform4;
	Platform Platform5;
	Platform Platform6;
	Platform Platform7;
	Platform Platform8;
	Platform Platform9;
	Platform Platform10;

	//player
	Player player;

	//furniture
	Buildings box1, box2, box3, box4;
	Buildings table1;
	Buildings chair1;
	Buildings keycard1;
	Buildings ladder;
	Buildings ladder2;
	Buildings ladder3;
	Buildings ladder4;

	//for quest
	vector<string> tasklist;
	Quest* questPtr;

	vector<GameObject*> collisionVec;


private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_indexBuffer[NUM_GEOMETRY];

	MS modelStack, viewStack, projectionStack, viewStack2;
	float f_rotateCube;
	Mesh* meshList[NUM_GEOMETRY];
	Light light[1];

	void RenderMesh(Mesh* mesh, bool enableLight);
	void RenderSkybox();
	void RenderSpaceVehicles(Camera3 camera);

	void RenderPingu();
	void RenderBB8(BB8 x);
	void RenderBB8v2(BB8v2 n);
	void RenderSuit();
	void RenderChestBurster();

	void RenderNecromancer();

	void RenderChestBurster1();

	void RenderSir(/*Sir n*/);
	void RenderPlatform(Platform p, bool isRotate);
	void RenderMedic(Medic x);

	void RenderGameObj(GameObject x, Mesh* mesh, bool enableLight = true, bool hasInteraction = false, Vector3 scale = Vector3(1, 1, 1), smaller axis = 0);
	void RenderGameChar(GameChar x, Mesh* mesh, bool enableLight = true, bool hasInteraction = false, Vector3 scale = Vector3(1, 1, 1));

	void Renderfps();
	void Rendertps();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, Vector3 translate = Vector3(0, 0, 0), Vector3 scale = Vector3(1, 1, 1), Vector3 rotate = Vector3(0, 0, 0));
};
#endif