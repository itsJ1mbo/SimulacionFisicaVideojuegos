#pragma once
#include "core.hpp"

class RenderItem;

class StaticRigidBody
{
public:
	StaticRigidBody(physx::PxScene* scene, physx::PxPhysics* physics,
		const Vector3& pos, const physx::PxGeometry& geometry, const Vector4& color);
	~StaticRigidBody();

	Vector3 position() const { return _actor->getGlobalPose().p; }

private:
	physx::PxRigidStatic* _actor;
	physx::PxTransform* _tr;
	RenderItem* _ri;
};

