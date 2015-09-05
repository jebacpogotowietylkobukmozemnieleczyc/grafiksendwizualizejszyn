#ifndef BULLET_HPP
#define BULLET_HPP
#include<memory>
#include <btBulletDynamicsCommon.h>
#include<DebugDrawer.h>
#include "GameObject.h"
#include "level.hpp"
class Bullet
{
public:
    Bullet();

~Bullet();
    auto getWorld () {return world;}
    auto getLevel () {return level;}
    //void InitBullet();
    void AddObject();
    void AddLevel();
//private:
    // core Bullet components
    std::unique_ptr<btCollisionConfiguration> collisionconfiguration;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btBroadphaseInterface> broadphase;
    std::unique_ptr<btConstraintSolver> solver;
    std::shared_ptr<btDynamicsWorld> world;

    std::unique_ptr<DebugDrawer> debugdrawer;
    GameObject* gameobject;
    GameObject* levelobject;
Level level;

};

#endif // BULLET_HPP
