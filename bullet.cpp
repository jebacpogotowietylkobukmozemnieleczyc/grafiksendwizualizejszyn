#include "bullet.hpp"
#include "iostream"

Bullet::Bullet(std::vector<GLfloat>& shadow)
    : collisionconfiguration(new btDefaultCollisionConfiguration()),
      dispatcher(new btCollisionDispatcher(collisionconfiguration.get())),
      broadphase(new btDbvtBroadphase()),
      solver(new btSequentialImpulseConstraintSolver()),
      world(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(),
                                        solver.get(),
                                        collisionconfiguration.get())),
      debugdrawer(new DebugDrawer()),
      level(4, -20, -20, 20, 20, 8, 8),
      solidsphere(shadow,2, 12 ,12) {
  world->setGravity(btVector3(0, 10, 0));
  debugdrawer->setDebugMode(0);
  world->setDebugDrawer(debugdrawer.get());
}

void Bullet::AddObject(btCollisionShape *pShape, float mass,
                       const btVector3 &color, const btVector3 &initialPosition,
                       const btQuaternion &initialRotation, float speed,
                       const btVector3 &direction) {
  std::function<void()> drawfunction;
  switch (shapetype) {
    case ShapeType::LEVEL:
      drawfunction = [&]() { level.DrawLevel(); };
      break;
    case ShapeType::SPHERE:
      drawfunction = [&]() { solidsphere.draw(0, 0, 0); };
      pShape = new btSphereShape(2);
      break;
    case ShapeType::CUBE:
      drawfunction = []() { glutSolidCube(4); };
      pShape = new btBoxShape(btVector3(2, 2, 2));
      break;
    case ShapeType::CONE:
      drawfunction = []() { glutSolidCone(2, 2, 20, 20); };
      pShape = new btConeShape(2, 2);
      break;
    case ShapeType::TEAPOT:
      drawfunction = []() { glutSolidTeapot(2); };
      pShape = new btSphereShape(2);
      break;
  }

  std::unique_ptr<GameObject> temp(new GameObject(
      drawfunction, pShape, mass, color, initialPosition, initialRotation));
  world->addRigidBody(temp->GetRigidBody());

  if (speed != 0) {

    btVector3 velocity = direction;
    velocity.normalize();
    velocity *= speed;

    temp->GetRigidBody()->setLinearVelocity(velocity);
  }
  gameobject.push_back(std::move(temp));
}

void Bullet::AddLevel() {
  btTriangleMesh *mesh = new btTriangleMesh;
  int x = 0;
  int z = 0;
  for (auto it = level.getVec().begin(); it != level.getVec().end(); it += 3) {
    if (x >= level.getDivx()) {
      ++z;
      x = 0;
      continue;
    }
    if (z >= level.getDivz())
      break;
    btVector3 newpoint(*(it), *(it + 1), *(it + 2));
    btVector3 newpoint2(*(it + (3 * (level.getDivx() + 1))),
                        *(it + (3 * (level.getDivx() + 1)) + 1),
                        *(it + (3 * (level.getDivx() + 1)) + 2));
    btVector3 newpoint3(*(it + 3), *(it + 4), *(it + 5));
    mesh->addTriangle(newpoint, newpoint2, newpoint3);
    btVector3 newpoint4(*(it + 3), *(it + 4), *(it + 5));
    btVector3 newpoint5(*(it + (3 * (level.getDivx() + 1))),
                        *(it + (3 * (level.getDivx() + 1)) + 1),
                        *(it + (3 * (level.getDivx() + 1)) + 2));
    btVector3 newpoint6(*(it + (3 * (level.getDivx() + 1)) + 3),
                        *(it + (3 * (level.getDivx() + 1)) + 4),
                        *(it + (3 * (level.getDivx() + 1)) + 5));
    mesh->addTriangle(newpoint4, newpoint5, newpoint6);
    ++x;
  }
  btBvhTriangleMeshShape *convexhullshape =
      new btBvhTriangleMeshShape(mesh, true);
  shapetype = ShapeType::LEVEL;
  AddObject(convexhullshape, 0, btVector3(0.0f, 0.0f, 0.0f),
            btVector3(0.0f, 0.0f, 0.0f), btQuaternion(1.0f, 0.0f, 0.0f, 0.0f),
            0.0f, btVector3(0.0f, 0.0f, 0.0f));
  shapetype = ShapeType::SPHERE;
  AddObject(
      nullptr, 1, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, -100.0f, 0.0f),
      btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), 0.0f, btVector3(0.0f, 0.0f, 0.0f));
}
