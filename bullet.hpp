#ifndef BULLET_HPP
#define BULLET_HPP
#include <btBulletDynamicsCommon.h>
#include<DebugDrawer.h>
#include "GameObject.h"
class Bullet
{
public:
    Bullet();

    void InitBullet();
    void InitDebug();
    void ClearBullet();
    void AddObject();
    btDynamicsWorld* world;
private:
    // core Bullet components
    btBroadphaseInterface* broadphase;
    btCollisionConfiguration* collisionconfiguration;
    btCollisionDispatcher* dispatcher;
    btConstraintSolver* solver;

    DebugDrawer* debugdrawer;
    GameObject* gameobject;

};

#endif // BULLET_HPP
