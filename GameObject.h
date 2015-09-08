#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <btBulletDynamicsCommon.h>

#include <functional>

class GameObject {
public:
  GameObject(std::function<void()> drawfunction, btCollisionShape* pShape,
             float mass, const btVector3& color,
             const btVector3& initialPosition = btVector3(0, 0, 0),
             const btQuaternion& initialRotation = btQuaternion(1, 0, 0, 0));
  ~GameObject();

  btCollisionShape* GetShape() { return m_pShape; }

  btRigidBody* GetRigidBody() { return m_pBody; }

  btMotionState* GetMotionState() { return m_pMotionState; }

  void GetTransform(btTransform& trans) {

    m_pBody->getMotionState()->getWorldTransform(trans);
  }

  btVector3 GetColor() { return m_color; }

  void SetColor(const btVector3& color) { m_color = color; }

  void DrawShape() { drawfunction(); }

protected:
  std::function<void()> drawfunction;
  btCollisionShape* m_pShape;
  btRigidBody* m_pBody;
  btDefaultMotionState* m_pMotionState;
  btVector3 m_color;
  btTriangleMesh* mesh;
};
#endif
