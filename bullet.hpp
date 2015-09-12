#ifndef BULLET_HPP
#define BULLET_HPP
#include <memory>
#include <btBulletDynamicsCommon.h>
#include <debugdrawer.h>
#include <GL/glut.h>
#include "gameobject.h"
#include "level.hpp"
#include "solidsphere.hpp"
enum class ShapeType { LEVEL, SPHERE, CUBE, CONE, TEAPOT };
class Bullet {
public:
  Bullet(std::vector<GLfloat>& shadow);

  const auto getWorld() const { return world; }
  auto& getLevel() { return level; }
   auto& getSolidSphere()  { return solidsphere; }
  const auto& getGameObject() const { return gameobject; }
  const auto& getDebugDrawer() const { return debugdrawer; }
  void setShapetype(ShapeType nshapetype) { shapetype = nshapetype; }
  void AddObject(btCollisionShape* pShape, float mass, const btVector3& color,
                 const btVector3& initialPosition,
                 const btQuaternion& initialRotation, float speed,
                 const btVector3& direction);
  void AddLevel();

private:
  std::unique_ptr<btCollisionConfiguration> collisionconfiguration;
  std::unique_ptr<btCollisionDispatcher> dispatcher;
  std::unique_ptr<btBroadphaseInterface> broadphase;
  std::unique_ptr<btConstraintSolver> solver;
  std::shared_ptr<btDynamicsWorld> world;

  std::unique_ptr<DebugDrawer> debugdrawer;
  std::vector<std::unique_ptr<GameObject> > gameobject;
  Level level;
  SolidSphere solidsphere;
  ShapeType shapetype;
};

#endif // BULLET_HPP
