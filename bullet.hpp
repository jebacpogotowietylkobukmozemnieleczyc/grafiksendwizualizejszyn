#ifndef BULLET_HPP
#define BULLET_HPP
#include<memory>
#include <btBulletDynamicsCommon.h>
#include<DebugDrawer.h>
#include <GL/glut.h>
#include "GameObject.h"
#include "level.hpp"
#include "solidsphere.hpp"
enum class ShapeType {LEVEL,SPHERE,CUBE,CONE,TEAPOT};
class Bullet
{
public:
    Bullet();

~Bullet();
    auto getWorld () {return world;}
    auto getLevel () {return level;}
void     setShapetype (ShapeType nshapetype) {shapetype=nshapetype;}
    //void InitBullet();
    void AddObject();
void AddObject(btCollisionShape* pShape, float mass,
        const btVector3 &color, const btVector3 &initialPosition,
        const btQuaternion &initialRotation,
                       float speed,
                       const btVector3 &direction);
    void AddLevel();

//private:
    // core Bullet components
    std::unique_ptr<btCollisionConfiguration> collisionconfiguration;
    std::unique_ptr<btCollisionDispatcher> dispatcher;
    std::unique_ptr<btBroadphaseInterface> broadphase;
    std::unique_ptr<btConstraintSolver> solver;
    std::shared_ptr<btDynamicsWorld> world;

    std::unique_ptr<DebugDrawer> debugdrawer;
    std::vector<std::unique_ptr<GameObject> > gameobject;
    GameObject* levelobject;
Level level;
SolidSphere solidsphere;
ShapeType shapetype;
};

#endif // BULLET_HPP
