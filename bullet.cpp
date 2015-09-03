#include "bullet.hpp"


 Bullet::Bullet():
    // create the collision configuration
    collisionconfiguration ( new btDefaultCollisionConfiguration()),
    // create the dispatcher
    dispatcher ( new btCollisionDispatcher(collisionconfiguration.get())),
    // create the broadphase
    broadphase ( new btDbvtBroadphase()),
    // create the constraint solver
    solver ( new btSequentialImpulseConstraintSolver()),
    // create the world
    world ( new btDiscreteDynamicsWorld(dispatcher.get(), broadphase.get(),
            solver.get(), collisionconfiguration.get())),
    // create the debug drawer
    debugdrawer ( new DebugDrawer())
{
    // set the initial debug level to 0
    debugdrawer->setDebugMode(0);
    // add the debug drawer to the world
    world->setDebugDrawer(debugdrawer.get());

        debugdrawer->ToggleDebugFlag(btIDebugDraw::DBG_DrawAabb);
}


void Bullet::AddObject(){

     gameobject= new GameObject(new btBoxShape(btVector3(2, 2, 3)), 0,
            btVector3(0.2f, 0.6f, 0.6f), btVector3(0.0f, 0.0f, 0.0f));
        world->addRigidBody(gameobject->GetRigidBody());
}
