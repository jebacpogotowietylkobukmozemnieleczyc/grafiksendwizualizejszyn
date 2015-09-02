#include "bullet.hpp"

Bullet::Bullet()
{

}

void Bullet::InitBullet(){
    // create the collision configuration
    collisionconfiguration = new btDefaultCollisionConfiguration();
    // create the dispatcher
    dispatcher = new btCollisionDispatcher(collisionconfiguration);
    // create the broadphase
    broadphase = new btDbvtBroadphase();
    // create the constraint solver
    solver = new btSequentialImpulseConstraintSolver();
    // create the world
    world = new btDiscreteDynamicsWorld(dispatcher, broadphase,
            solver, collisionconfiguration);

}
void Bullet::InitDebug(){
    // create the debug drawer
    debugdrawer = new DebugDrawer();
    // set the initial debug level to 0
    debugdrawer->setDebugMode(0);
    // add the debug drawer to the world
    world->setDebugDrawer(debugdrawer);

        debugdrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawAabb);
}

void Bullet::ClearBullet(){
     // create the collision configuration
    delete collisionconfiguration ;
    // create the dispatcher
    delete dispatcher;
    // create the broadphase
    delete broadphase;
    // create the constraint solver
    delete solver;
    // create the world
    delete world;

   delete debugdrawer;

    delete gameobject;
}

void Bullet::AddObject(){

     gameobject= new GameObject(new btBoxShape(btVector3(2, 2, 3)), 0,
            btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));
        world->addRigidBody(gameobject->GetRigidBody());
}
