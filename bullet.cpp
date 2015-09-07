#include "bullet.hpp"
#include "iostream"

Bullet::Bullet()
    : // create the collision configuration
      collisionconfiguration(new btDefaultCollisionConfiguration()),
      // create the dispatcher
      dispatcher(new btCollisionDispatcher(collisionconfiguration.get())),
      // create the broadphase
      broadphase(new btDbvtBroadphase()),
      // create the constraint solver
      solver(new btSequentialImpulseConstraintSolver()),
      // create the world
      world(new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(),
                                        solver.get(),
                                        collisionconfiguration.get())),
      // create the debug drawer
      debugdrawer(new DebugDrawer()),
      level(NULL, 4, -10, -10, 10, 20, 8, 8) ,
solidsphere(2,12,14)
{
  world->setGravity(btVector3(0, 10, 0));
  // set the initial debug level to 0
  debugdrawer->setDebugMode(0);
  // add the debug drawer to the world
  world->setDebugDrawer(debugdrawer.get());

  debugdrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawWireframe);
}

void Bullet::AddObject(
                       btCollisionShape *pShape, float mass,
                       const btVector3 &color, const btVector3 &initialPosition,
                       const btQuaternion &initialRotation, float speed,
                       const btVector3 &direction) {
    std::function<void()> drawfunction;
    switch(shapetype){
    case ShapeType::LEVEL:
        drawfunction = [&]() { level.DrawLevel(); };
                break;
    case ShapeType::SPHERE:
        drawfunction = [&]() { solidsphere.draw(0,0,0);  };
        pShape=new btSphereShape(2) ;
                break;
    case ShapeType::CUBE:
        drawfunction = []() { glutSolidCube(4);  };
        pShape=new btBoxShape(btVector3(2, 2, 2));
                break;
    case ShapeType::CONE:
        drawfunction = []() { glutSolidCone(2,2, 20, 20);  };
        pShape=new btConeShape(2, 2 );
                break;
    case ShapeType::TEAPOT:
        drawfunction = []() { glutSolidTeapot(2);  };
        pShape=new btSphereShape(2) ;
                break;
    }

  std::unique_ptr<GameObject> temp(new GameObject(
      drawfunction, pShape, mass, color, initialPosition, initialRotation));
  world->addRigidBody(temp->GetRigidBody());

  if (speed != 0) {

    btVector3 velocity = direction;
    velocity.normalize();
    velocity *= speed;

    // set the linear velocity of the box
    temp->GetRigidBody()->setLinearVelocity(velocity);
  }
  gameobject.push_back(std::move(temp));
  // gameobject= new GameObject(new btBoxShape(btVector3(2, 2, 3)), 0,
  //      btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));
  // world->addRigidBody(gameobject->GetRigidBody());
}

void Bullet::AddLevel() {
  /*
      btConvexHullShape* convexhullshape = new btConvexHullShape;
      for(auto it = level.getVec().begin(); it != level.getVec().end(); it+=3) {
          btVector3 newpoint(*(it),*(it+1),*(it+2));
          //btVector3 newpoint2(*(it),-5.0f,*(it+2));
         convexhullshape->addPoint(newpoint);
         //convexhullshape->addPoint(newpoint2);
  }
      */
  btTriangleMesh *mesh = new btTriangleMesh;
  int v = 0;
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
    // if(*(it)>=level.getDivx() || *(it+2)>=level.getDivz())continue;
    btVector3 newpoint(*(it), *(it + 1), *(it + 2));
    btVector3 newpoint2(*(it + (3 * (level.getDivx() + 1))),
                        *(it + (3 * (level.getDivx() + 1)) + 1),
                        *(it + (3 * (level.getDivx() + 1)) + 2));
    btVector3 newpoint3(*(it + 3), *(it + 4), *(it + 5));
    mesh->addTriangle(newpoint, newpoint2, newpoint3);
    std::cout << ++v << "Mesh: " << newpoint.x() << " " << newpoint.y() << " "
              << newpoint.z() << std::endl;
    std::cout << ++v << "Mesh: " << newpoint2.x() << " " << newpoint2.y() << " "
              << newpoint2.z() << std::endl;
    std::cout << ++v << "Mesh: " << newpoint3.x() << " " << newpoint3.y() << " "
              << newpoint3.z() << std::endl;

    btVector3 newpoint4(*(it + 3), *(it + 4), *(it + 5));
    btVector3 newpoint5(*(it + (3 * (level.getDivx() + 1))),
                        *(it + (3 * (level.getDivx() + 1)) + 1),
                        *(it + (3 * (level.getDivx() + 1)) + 2));
    btVector3 newpoint6(*(it + (3 * (level.getDivx() + 1)) + 3),
                        *(it + (3 * (level.getDivx() + 1)) + 4),
                        *(it + (3 * (level.getDivx() + 1)) + 5));
    mesh->addTriangle(newpoint4, newpoint5, newpoint6);
    std::cout << ++v << "Mesh: " << newpoint4.x() << " " << newpoint4.y() << " "
              << newpoint4.z() << std::endl;
    std::cout << ++v << "Mesh: " << newpoint5.x() << " " << newpoint5.y() << " "
              << newpoint5.z() << std::endl;
    std::cout << ++v << "Mesh: " << newpoint6.x() << " " << newpoint6.y() << " "
              << newpoint6.z() << std::endl;
    ++x;
  }
  int xd = 0;
  std::cout << "start ";
  for (auto it = level.getVec().begin(); it != level.getVec().end(); ++it) {
    // std::cout << *(it) << " ";
    xd++;
  }
  std::cout << std::endl << "YOYOYOYOYO" << xd << std::endl;
  /*
  for(auto it = level.getVec().begin(); it != level.getVec().end(); it+=3) {
      if(*(it)>=level.getDivx() || *(it+2)>=level.getDivz())continue;
      btVector3 newpoint(*(it),-5.0f,*(it+2));
      btVector3
  newpoint2(*(it+(3*(level.getDivx()+1))),-5.0f,*(it+(3*(level.getDivx()+2))));
      btVector3 newpoint3(*(it+3),-5.0f,*(it+5));
      mesh->addTriangle(newpoint,newpoint2,newpoint3);
      std::cout << "Mesh: " << newpoint.x() << " "<< newpoint.y() << " "<<
  newpoint.z() <<std::endl;
      std::cout << "Mesh: " << newpoint2.x() << " "<< newpoint2.y() << " "<<
  newpoint2.z() <<std::endl;
      std::cout << "Mesh: " << newpoint3.x() << " "<< newpoint3.y() << " "<<
  newpoint3.z() <<std::endl;

      btVector3 newpoint4(*(it+3),-5.0f,*(it+5));
      btVector3
  newpoint5(*(it+(3*(level.getDivx()+1))),-5.0f,*(it+(3*(level.getDivx()+1))+2));
      btVector3
  newpoint6(*(it+(3*(level.getDivx()+1))+3),-5.0f,*(it+(3*(level.getDivx()+1))+5));
      mesh->addTriangle(newpoint4,newpoint5,newpoint6);
      std::cout << "Mesh: " << newpoint4.x() << " "<< newpoint4.y() << " "<<
  newpoint4.z() <<std::endl;
      std::cout << "Mesh: " << newpoint5.x() << " "<< newpoint5.y() << " "<<
  newpoint5.z() <<std::endl;
      std::cout << "Mesh: " << newpoint6.x() << " "<< newpoint6.y() << " "<<
  newpoint6.z() <<std::endl;
  }
  */
  btBvhTriangleMeshShape *convexhullshape =
      new btBvhTriangleMeshShape(mesh, true);
shapetype = ShapeType::LEVEL;
  AddObject( convexhullshape, 0,
            btVector3(0.0f, 0.0f, 0.0f), btVector3(0.0f, 0.0f, 0.0f),
            btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), 0.0f,
            btVector3(0.0f, 0.0f, 0.0f));
shapetype = ShapeType::CUBE;
  AddObject(
              nullptr,
      1, btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, -100.0f, 0.0f),
      btQuaternion(1.0f, 0.0f, 0.0f, 0.0f), 0.0f, btVector3(0.0f, 0.0f, 0.0f));
  }

Bullet::~Bullet() { delete levelobject; }
