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

void CameraTPS::Init(const Vector3& pos, const Vector3& up, const Vector3& vehiclePos)
{
    this->position = pos;
    this->target = vehiclePos;
    this->view = (target - position).Normalized();
    right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    defaultUp = right.Cross(view).Normalized();
    cameraRotationX = 0.0f;
    cameraRotationY = 0.0f;
}

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
        cos(Math::DegreeToRadian(cameraRotationY)) * cos(Math::DegreeToRadian(cameraRotationX)) + this->target.x, // target.x // position + Math...
        sin(Math::DegreeToRadian(cameraRotationX)) + this->target.y,
        -sin(Math::DegreeToRadian(cameraRotationY))  * cos(Math::DegreeToRadian(cameraRotationX)) + this->target.z
        );

}

void CameraTPS::tpsUpdateVec(Vector3 targetVec)
{
    this->target = targetVec;
    tpsUpdateRotation(50);
    //this->position = (Vector3(vec.x, vec.y + 20, vec.z) - (Vector3(cam.view.x, 0, cam.view.z).Normalized()) * 80);
    view = target - position;
    right = view.Cross(defaultUp);
    right.y = 0;
    right.Normalize();
    this->up = right.Cross(view).Normalized();
}