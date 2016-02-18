#ifndef SP2_SCENE1_H
#define SP2_SCENE1_H

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



class Object
{
public:
	Position position;
	int State;
	std::string Message;

	enum States
	{
		patrol,
		target,
	};
};

enum Objects
{
	NPC,
	Num_Obj,
};

class Sp2_Scene1 : public Scene
{
public:
	Sp2_Scene1();
	~Sp2_Scene1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_LIGHTBALL,

		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		GEO_SPHERE,

		GEO_TEXT,
		GEO_TEXTBACKGROUND,

		/*<---Studio Project 2--->*/
		/*<---Space Vehicles--->*/
		//GEO_SECOND,
		//GEO_THIRD,
		GEO_FOURTH,
		//GEO_FIFTH,
		//GEO_MOTOR,
		//GEO_ROVER,
		//GEO_FIREFLY,
		//GEO_ENEMYVEHICLE,
		//GEO_MOONROVER,
		//GEO_ENEMY2,
		GEO_NPCLEPUSMAG,

        GEO_SNIPERRIFLE,
        GEO_DART,

		/*<---NPC--->*/
		GEO_NPC1,
		GEO_NPC2,

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

	float rotateAngle;
	float translateX;
	float scaleAll;

	Camera3 camera;
	CameraTPS camera2;

	float LSPEED;
	bool b_lightEnabled;
	int screenWidth, screenHeight;
	Vector3 tempPos;
	bool b_enabletps;
	bool b_tpsDebounce;
	float tpsTimer;
	Vector3 ffposition;
    Gun laserRifle;
    Vector3 trajectory;

	//SpaceVehicles ff;
	//SpaceVehicles mr;
	//SpaceVehicles ev;
	//SpaceVehicles e2;
	SpaceVehicles np;

	/**/

	//SpaceVehicles spc;
	//SpaceVehicles tpc;
	SpaceVehicles frpc;
	//SpaceVehicles fifpc;
	//SpaceVehicles mtv;
	//SpaceVehicles rov;

	Human npc1;
	Alien npc2;

public:
	/**/
	Object objects[Num_Obj];
	int Timer;

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
	void RenderSkybox(Camera3 camera);
	void RenderSpaceVehicles(Camera3 camera);

	/**/
	//void Renderff(SpaceVehicles ff);
	//void RenderMR(SpaceVehicles mr);
	//void Renderev(SpaceVehicles ev);
	//void Rendere2(SpaceVehicles e2);
	void Rendernp(SpaceVehicles np);
	/**/
	//void RenderSPC(SpaceVehicles spc);
	//void RenderTPC(SpaceVehicles tpc);
	void RenderFRPC(SpaceVehicles frpc);
	//void RenderFIFPC(SpaceVehicles fifpc);
	//void RenderMTV(SpaceVehicles mtv);
	//void RenderROV(SpaceVehicles rov);
	/**/
	void RenderNPC1(Human npc1);
	void RenderNPC2(Alien npc2);

	void Renderfps();
	void Rendertps();



	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

};

#endif