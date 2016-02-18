#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
extern GLFWwindow* m_window;


Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up, float bound)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	CameraSpeed = 0.25f;
	cameraRotationX = 0.0f;
	cameraRotationY = 0.0f;
	movementSpeed = 100;
	f_jumpSpeed = 50;
	f_jumpAcceleration = 75;
	b_jumping = false;
	b_jumpUP = true;
	boundary = bound;

}

void Camera3::updateRotation(float CameraSpeed) // camerarotationx and y, 38 to 48
{
	int screenSizeX, screenSizeY;
	int midScreenX, midScreenY;
	glfwGetWindowSize(m_window,&screenSizeX,&screenSizeY);
	midScreenX = screenSizeX / 2;
	midScreenY = screenSizeY / 2;
	//checking for the position of the mouse cursor and resetting it every frame
	POINT mousePos;
	GetCursorPos(&mousePos);
	SetCursorPos(midScreenX, midScreenY);
	cameraRotationY -= (mousePos.x - midScreenX) / (1.0f / CameraSpeed);
	cameraRotationX -= (mousePos.y - midScreenY) / (1.0f / CameraSpeed);
	if (cameraRotationX >80)
	{
		cameraRotationX = 80;
	}
	else if (cameraRotationX < -80)
	{
		cameraRotationX = -80;
	}
	if (cameraRotationY >=360 || cameraRotationY <= -360)
	{
		cameraRotationY = 0;
	}

	target = Vector3 // position
		(
		cos(Math::DegreeToRadian(cameraRotationY)) * cos(Math::DegreeToRadian(cameraRotationX))+ this->position.x, // target.x // position + Math...
		sin(Math::DegreeToRadian(cameraRotationX))+this->position.y,
		-sin(Math::DegreeToRadian(cameraRotationY))  * cos(Math::DegreeToRadian(cameraRotationX)) + this->position.z
		);
	
}

void Camera3::Update(double dt)
{


	static const float CAMERA_SPEED = 50.f;

	
	//else
	//{
	//	boundary = 800;
	//}
	view = (target - position).Normalized();
	right = view.Cross(defaultUp);
	right.y = 0;
	right.Normalize();
	this->up = right.Cross(view).Normalized();

	if (Application::IsKeyPressed('W'))
	{
		view = (Vector3(target.x, 0, target.z) - Vector3(position.x, 0, position.z)).Normalized();
		position += view *(float)( movementSpeed * dt);

	}

	if (Application::IsKeyPressed('S'))
	{
		view = (Vector3(target.x, 0, target.z) - Vector3(position.x, 0, position.z)).Normalized();
		position -= view *(float)(movementSpeed * dt);

	}

	if (Application::IsKeyPressed('A'))
	{
		position -= right * (movementSpeed/45);

		
	}
	if (Application::IsKeyPressed('D'))
	{
		position += right* (movementSpeed/45);

	}

	if (Application::IsKeyPressed('Q'))
	{
		position += Vector3(0, movementSpeed / 25, 0);
	}

	if (Application::IsKeyPressed(VK_SPACE) && b_jumping == false)
	{
		b_jumpUP = true;
		b_jumping = true;
	}

	if (b_jumpUP == true && b_jumping == true)
	{
		f_jumpSpeed -= f_jumpAcceleration * dt;
		position += Vector3(0, f_jumpSpeed, 0) * (float)dt;
		if (f_jumpSpeed <= 0.0f)
		{
			b_jumpUP = false;
		}
	}

	else if (b_jumpUP == false && b_jumping == true)
	{
		f_jumpSpeed += f_jumpAcceleration * dt;
		position -= Vector3(0, f_jumpSpeed, 0) * (float)dt;
		if (f_jumpSpeed >= 50.0f)
		{
			position.y = 0;
			b_jumpUP = true;
			b_jumping = false;
		}
	}


	if (Application::IsKeyPressed('R'))
	{
		Reset();
	}
	updateRotation(CameraSpeed);
}

void Camera3::updateRotationTps(float cameraSpeed)
{

	int screenSizeX, screenSizeY;
	int midScreenX, midScreenY;
	glfwGetWindowSize(m_window, &screenSizeX, &screenSizeY);
	midScreenX = screenSizeX / 2;
	midScreenY = screenSizeY / 2;
	//checking for the position of the mouse cursor and resetting it every frame
	POINT mousePos;
	GetCursorPos(&mousePos);
	SetCursorPos(midScreenX, midScreenY);
	cameraRotationY -= (mousePos.x - midScreenX) / (1.0f / CameraSpeed);
	cameraRotationX -= (mousePos.y - midScreenY) / (1.0f / CameraSpeed);
	if (cameraRotationX >80)
	{
		cameraRotationX = 80;
	}
	else if (cameraRotationX < -80)
	{
		cameraRotationX = -80;
	}
	if (cameraRotationY >= 360 || cameraRotationY <= -360)
	{
		cameraRotationY = 0;
	}
	position = Vector3
		(
		target.x + cos(Math::DegreeToRadian(cameraRotationY))*cos(Math::DegreeToRadian(cameraRotationX))*80,
		35,
		target.z + sin(Math::DegreeToRadian(cameraRotationY))*cos(Math::DegreeToRadian(cameraRotationX)) * 80
		);
}

void Camera3::tpsUpdate(Camera3 cam,double dt)
{
	this->target = cam.position;
	//updateRotationTps(50);
	this->position =( Vector3(cam.position.x, cam.position.y+20, cam.position.z) - (Vector3(cam.view.x, 0, cam.view.z).Normalized())* 80 );
	view = (target - position).Normalized();
	right = view.Cross(defaultUp);
	right.y = 0;
	right.Normalize();
	this->up = right.Cross(view).Normalized();
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	CameraSpeed = 0.25f;
	cameraRotationX = 0.0f;
	cameraRotationY = 0.0f;
	movementSpeed = 25;
	f_jumpSpeed = 10;
	f_jumpAcceleration = 10;
	b_jumping = false;
	b_jumpUP = true;
}