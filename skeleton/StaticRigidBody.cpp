#include "StaticRigidBody.h"

#include "RenderUtils.hpp"

StaticRigidBody::StaticRigidBody(physx::PxScene* scene, physx::PxPhysics* physics, const Vector3& pos,
                                 const physx::PxGeometry& geometry, const Vector4& color) :
		_actor(nullptr),
		_tr(new physx::PxTransform(pos)),
		_ri(nullptr)
{
	_actor = physics->createRigidStatic(*_tr);
	physx::PxShape* shape = CreateShape(geometry);
	_actor->attachShape(*shape);

	scene->addActor(*_actor);

	_ri = new RenderItem(shape, _actor, color);
}

StaticRigidBody::~StaticRigidBody()
{
	DeregisterRenderItem(_ri);
	_ri = nullptr;

	delete _tr;
	_tr = nullptr;

	_actor->release();
	_actor = nullptr;
}
