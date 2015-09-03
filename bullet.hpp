#ifndef BULLET_HPP
#define BULLET_HPP
#include<memory>
#include <btBulletDynamicsCommon.h>
#include<DebugDrawer.h>
#include "GameObject.h"
class Bullet
{
public:
    Bullet();

    auto getWorld () {return world;}
    //void InitBullet();
    void AddObject();
private:
    // core Bullet components
    std::unique_ptr<btCollisionConfiguration> collisionconfiguration;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btBroadphaseInterface> broadphase;
    std::unique_ptr<btConstraintSolver> solver;
    std::shared_ptr<btDynamicsWorld> world;

    std::unique_ptr<DebugDrawer> debugdrawer;
    GameObject* gameobject;

};

#endif // BULLET_HPP
