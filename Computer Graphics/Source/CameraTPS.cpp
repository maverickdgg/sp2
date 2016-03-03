#include "CameraTPS.h"
#include "Application.h"
#include "Mtx44.h"
extern GLFWwindow* m_window;

CameraTPS::CameraTPS()
{
}

CameraTPS::~CameraTPS()
{
}
/******************************************************************************/
/*!
\brief
intialise third person camera
*/
/******************************************************************************/
void CameraTPS::Init(const Vector3& pos, const Vector3& up, GameObject* targetObj)
{

	this->targetObj = targetObj;
    this->defaultOffset = pos;
    this->target = targetObj->pos;

	this->position = target + defaultOffset;
	this->view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();

    cameraRotationX = 0.0f;
    cameraRotationY = 0.0f;
	b_cameraLock = false;
	b_cameraLockDebounce = false;

}
/******************************************************************************/
/*!
\brief
update the rotation of the camera based on mouse
\param speed
rotation speed (mouse sensitivity)
*/
/******************************************************************************/
void CameraTPS::tpsUpdateRotation(float speed)
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
	cameraRotationY -= (mousePos.x - midScreenX) / (1.0f / speed);
	cameraRotationX -= (mousePos.y - midScreenY) / (1.0f / speed);
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

	position = Vector3 // position
		(
		cos(Math::DegreeToRadian(cameraRotationY)) * defaultOffset.x + this->target.x, // target.x // position + Math...
		defaultOffset.y + this->target.y,
		sin(Math::DegreeToRadian(cameraRotationY))* defaultOffset.z + this->target.z
		);

}
/******************************************************************************/
/*!
\brief
update of the third person camera
\param dt
delta time
*/
/******************************************************************************/
void CameraTPS::tpsUpdateVec(double dt)
{

	if (Application::IsKeyPressed('L') && b_cameraLockDebounce == false && b_cameraLock == false)
	{
		b_cameraLockDebounce = true;
		b_cameraLock = true;
	}
	else if (Application::IsKeyPressed('L') && b_cameraLockDebounce == false && b_cameraLock == true)
	{
		b_cameraLockDebounce = true;
		b_cameraLock = false;
	}
	if (!Application::IsKeyPressed('L') && b_cameraLockDebounce == true)
	{
		b_cameraLockDebounce = false;
	}
	if (b_cameraLock == false)
	{
		this->target = (targetObj->pos);
		tpsUpdateRotation(0.3);
		view = (target - position).Normalized();
		right = view.Cross(defaultUp);
		right.y = 0;
		right.Normalize();
		this->up = right.Cross(view).Normalized();
	}
	else
	{
		this->target = targetObj->pos;
		cameraRotationY = -(targetObj->viewAngle) + 90;
		this->position = Vector3 // position
			(
			cos(Math::DegreeToRadian(cameraRotationY)) * defaultOffset.x + this->target.x, // target.x // position + Math...
			//sin(Math::DegreeToRadian(cameraRotationX)) * defaultOffset.y  + this->target.y,
			defaultOffset.y + this->target.y,
			sin(Math::DegreeToRadian(cameraRotationY))* defaultOffset.z + this->target.z
			);
		view = (target - position).Normalized();
		right = view.Cross(defaultUp);
		right.y = 0;
		right.Normalize();
		this->up = right.Cross(view).Normalized();
	}
}
