#include "Gun.h"

size_t Gun::G_count = 0;

Gun::Gun() : totalAmmo(1), currAmmo(1), magCap(30), maxAmmo(200), position(Vector3(0, 0, 0))
{
    ++G_count;
}

Gun::Gun(string name, int boundary, Vector3 pos) : Weapon(name, boundary, 0, pos), totalAmmo(1), currAmmo(1), magCap(30), maxAmmo(200), position(Vector3(0, 0, 0))
{
    for (int i = 0; i < 30; ++i)
    {
        magazine.push_back(Bullet(2, 0, Vector3(2000, 2000, 2000)));
    }
    ++G_count;
}

Gun::~Gun()
{
    --G_count;
}

bool Gun::fire(Vector3 view, float dt)
{
    if ((VK_LBUTTON)& 0x80)
    {
        bulletVec = view;
        view.Normalize();
        position += view  * dt * attackSpeed;
        return true;
    }
}

float Gun::findAngle(Vector3 view)
{
    view = Vector3(view.x, 0, view.z);
    if (view.z >=0)
        viewAngle = Math::RadianToDegree(atan(view.x / view.z))-90 ;
    else
        viewAngle = Math::RadianToDegree(atan(view.x/view.z)) - 180 -90;
    return viewAngle;
}
