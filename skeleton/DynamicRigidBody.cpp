#include "DynamicRigidBody.h"

#include <iostream>

#include "RenderUtils.hpp"

DynamicRigidBody::DynamicRigidBody(physx::PxScene* scene, physx::PxPhysics* physics, 
	const Vector3& pos, const physx::PxGeometry& geometry, const Vector4& color, 
	const float d) :
		_actor(nullptr),
		_tr(new physx::PxTransform(pos)),
		_ri(nullptr)
{
	_actor = physics->createRigidDynamic(*_tr);
	_actor->setLinearVelocity(Vector3(0, 0, 0));
	_actor->setAngularVelocity(Vector3(0, 0, 0));
	physx::PxShape* shape = CreateShape(geometry);
	_actor->attachShape(*shape);
	physx::PxRigidBodyExt::updateMassAndInertia(*_actor, d);

	scene->addActor(*_actor);

	_ri = new RenderItem(shape, _actor, color);
}

DynamicRigidBody::~DynamicRigidBody()
{
	DeregisterRenderItem(_ri);
	_ri = nullptr;

	delete _tr;
	_tr = nullptr;

	_actor->release();
	_actor = nullptr;
}

void DynamicRigidBody::add_force(const Vector3& force) const
{
	_actor->addForce(force);

	//std::cout << "POS: " << _actor->getGlobalPose().p.x << " " << _actor->getGlobalPose().p.y << " " << _actor->getGlobalPose().p.z << std::endl;
}
