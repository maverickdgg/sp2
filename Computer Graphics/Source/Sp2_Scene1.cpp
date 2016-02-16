#include "Sp2_Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "LoadTGA.h"

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

	camera.Init(Vector3(0, 0, 0), Vector3(10, 0, 0), Vector3(0, 1, 0), 180);
	//camera2.Init(Vector3(0, 0, 50), camera.position, Vector3(0, 1, 0), 500);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("AXES", 1000, 1000, 1000);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//color2.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//Assn3_front.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//Assn3_bottom.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//Assn3_back.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//Assn3_top.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//Assn3_left.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//Assn3_right.tga");

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0));
	

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("LIGHTBALL", Color(1, 0, 1));

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_TEXTBACKGROUND] = MeshBuilder::GenerateQuad("quad", Color(0, 0, 11), 1.f, 1.f);
	
	meshList[GEO_FIREFLY] = MeshBuilder::GenerateOBJ("Firefly","OBJs//Firefly.obj");
	meshList[GEO_FIREFLY]->textureID = LoadTGA("Image//Firefly.tga");


	/*<---Studio Project 2--->*/
	meshList[GEO_SECOND] = MeshBuilder::GenerateOBJ("secondplayercontrolled", "OBJ//SecondPlayerControlledAircraft.obj");
	meshList[GEO_SECOND]->textureID = LoadTGA("Image//SecondPlayerControlledAircraft.tga");

	meshList[GEO_THIRD] = MeshBuilder::GenerateOBJ("thirdplayercontrolled", "OBJ//ThirdPlayerControlled.obj");
	meshList[GEO_THIRD]->textureID = LoadTGA("Image//ThirdPlayerControlled.tga");

	meshList[GEO_FOURTH] = MeshBuilder::GenerateOBJ("fourthplayercontrolled", "OBJ//FourthPlayerControlled.obj");
	meshList[GEO_FOURTH]->textureID = LoadTGA("Image//FourthPlayerControlled.tga");

	meshList[GEO_FIFTH] = MeshBuilder::GenerateOBJ("fifthplayercontrolled", "OBJ//FifthPlayerControlled.obj");
	meshList[GEO_FIFTH]->textureID = LoadTGA("Image//FifthPlayerControlled.tga");

	meshList[GEO_MOTOR] = MeshBuilder::GenerateOBJ("motorlandvehicle", "OBJ//MotorLandVehicle.obj");
	meshList[GEO_MOTOR]->textureID = LoadTGA("Image//MotorLandVehicle.tga");

	meshList[GEO_ROVER] = MeshBuilder::GenerateOBJ("roverlandvehicle", "OBJ//RoverLandVehicle.obj");
	meshList[GEO_ROVER]->textureID = LoadTGA("Image//RoverLandVehicle.tga");

	b_enabletps = false;
	b_tpsDebounce = false;
	tpsTimer = 0;
}


void Sp2_Scene1::Update(double dt)
{
	//camera.Update(dt);
	//camera2.tpsUpdate(camera, dt);

	camera.view = (camera.target - camera.position).Normalized();
	camera.right = camera.view.Cross(camera.defaultUp);
	camera.right.y = 0;
	camera.right.Normalize();
	this->camera.up = camera.right.Cross(camera.view).Normalized();

	
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

	
	if (Application::IsKeyPressed('W'))
	{
		
		//cam movement
		
		camera.view = (Vector3(camera.target.x, 0, camera.target.z) - Vector3(camera.position.x, 0, camera.position.z)).Normalized();
		camera.position += camera.view *(float)(camera.movementSpeed * dt);

	}
	if (Application::IsKeyPressed('S'))
	{
		
		//cam movement
		camera.view = (Vector3(camera.target.x, 0, camera.target.z) - Vector3(camera.position.x, 0, camera.position.z)).Normalized();
		camera.position -= camera.view *(float)(camera.movementSpeed * dt);



	}

	if (Application::IsKeyPressed('A'))
	{
		camera.position -= camera.right * (camera.movementSpeed / 45);	
	}

	if (Application::IsKeyPressed('D'))
	{
		camera.position += camera.right * (camera.movementSpeed / 45);
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
			camera.position.y = 13;
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
	if (!Application::IsKeyPressed(VK_MENU))
	{
		camera.updateRotation(0.3);
		ShowCursor(FALSE);
	}

	if (Application::IsKeyPressed(VK_MENU))
	{
		ShowCursor(TRUE);
	}

	//camera2.tpsUpdate(camera, dt);
	
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
	modelStack.Translate(0,0,0);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(1,1,1);
	RenderMesh(meshList[GEO_FIREFLY], false);
	modelStack.PopMatrix();
	
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

void Sp2_Scene1::Renderfps()
{


	RenderSkybox(camera);

	RenderMesh(meshList[GEO_AXES], false);


	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_SPHERE], false);
	modelStack.PopMatrix();
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
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

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

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_SECOND], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 0);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_THIRD], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 12, 0);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_FOURTH], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 20, 0);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_FIFTH], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 50, 0);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(1, 1, 1);
	RenderMesh(meshList[GEO_MOTOR], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 60, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ROVER], false);
	modelStack.PopMatrix();
}



void Sp2_Scene1::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}