#ifndef GUN_H
#define GUN_H
#include "Weapon.h"
#include "Bullet.h"
#include "Application.h"

class Gun : public Weapon
{
public:
    Gun();
    Gun(string object_name, int boundary, Vector3 pos = Vector3(0, 0, 0));
    ~Gun();
    static size_t G_count;
    smaller totalAmmo;
    smaller currAmmo;
    smaller magCap; // capacity of clip
    smaller maxAmmo; // max of all guns(clip should not be more than max)
    Vector3 view;
    Vector3 direction; // where snout of barrel is pointing
    Vector3 position;
    Vector3 bulletVec;
    float viewAngle2;
    float findAngle(Vector3 view = Vector3(0, 0, 0)); // used to store angle based on view vector and direction gun is pointing
    bool fire(Vector3 view, float deltaTime); // rotate to viewangle and trans based on view vector
    vector<Bullet> magazine;
};

#endif