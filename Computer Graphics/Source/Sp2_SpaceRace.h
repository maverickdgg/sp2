#ifndef SP2_SPACERACE_H
#define SP2_SPACERACE_H

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
#include "Player.h"
#include "BB-8.h"
#include "Pingu.h"
#include "Quest.h"
#include "AlienEnemy.h"
#include "Map.h"

class Sp2_SpaceRace : public Scene
{
public:
	Sp2_SpaceRace();
	~Sp2_SpaceRace();

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
		GEO_HELM,

		/*<---NPC--->*/
		GEO_MIKE,	// Default (Pure Interaction Codes, no NPC)	
		GEO_NPC3,	// Storm Trooper
		GEO_FLIGHTUI,	// Astronaut Suit
		GEO_BB8H,	// BB-8 Head
		GEO_BB8B,	// BB-8 Body
		GEO_PINGU,
		GEO_CHESTBURSTER,

		GEO_PINGUBODY,
		GEO_PINGULH,
		GEO_PINGURH,

		GEO_BOX,
		GEO_TABLE,
		GEO_CHAIR,
		GEO_KEYCARD,
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
	float tpsTimer;

	SpaceVehicles frpc;

	//player
	Player player;

	//furniture
	Buildings box1, box2, box3, box4;
	Buildings table1;
	Buildings chair1;
	Buildings keycard1;

	//for quest
	vector<string> tasklist;
	Quest* questPtr;

	vector<GameObject*> collisionVec;

	string speed;
	PMAP racetrack;


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
	void RenderSkybox(Camera cam);

	void RenderGameObj(GameObject x, Mesh* mesh, bool enableLight = true, bool hasInteraction = false, Vector3 scale = Vector3(1, 1, 1), Vector3 rotate = Vector3(0, 0, 0));
	void RenderGameChar(GameChar x, Mesh* mesh, bool enableLight = true, bool hasInteraction = false, Vector3 scale = Vector3(1, 1, 1), Vector3 rotate = Vector3(0, 0, 0));

	void Renderfps();
	void Rendertps();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshOnScreen(Mesh* mesh, Vector3 translate = Vector3(0, 0, 0), Vector3 scale = Vector3(1, 1, 1), Vector3 rotate = Vector3(0, 0, 0));
};
#endif