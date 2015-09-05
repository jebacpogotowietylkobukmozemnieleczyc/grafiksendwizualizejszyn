#include "GameObject.h"
GameObject::GameObject(std::function<void()> drawfunction,btCollisionShape* pShape, float mass,
		const btVector3 &color, const btVector3 &initialPosition,
        const btQuaternion &initialRotation):
    drawfunction(drawfunction),
    m_pShape ( pShape),
    m_color ( color),
    mesh(nullptr)
{
	// create the initial transform
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(initialPosition);
	transform.setRotation(initialRotation);

	// create the motion state from the
	// initial transform
    m_pMotionState = new btDefaultMotionState(transform);

	// calculate the local inertia
	btVector3 localInertia(0, 0, 0);

	// objects of infinite mass can't
	// move or rotate
	if (mass != 0.0f)
		pShape->calculateLocalInertia(mass, localInertia);

	// create the rigid body construction
	// info using the mass, motion state
	// and shape
	btRigidBody::btRigidBodyConstructionInfo cInfo(mass, m_pMotionState, pShape,
			localInertia);

	// create the rigid body
	m_pBody = new btRigidBody(cInfo);
}

GameObject::~GameObject()
{
	delete m_pBody;
	delete m_pMotionState;
	delete m_pShape;
    if(mesh!=nullptr)
delete mesh;
}
