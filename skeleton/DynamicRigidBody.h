#pragma once
#include "core.hpp"

class RenderItem;

class DynamicRigidBody
{
public:
	DynamicRigidBody(physx::PxScene* scene, physx::PxPhysics* physics, const Vector3& pos, const physx::PxGeometry& geometry,
		const Vector4& color, float d);
	~DynamicRigidBody();

	void add_force(const Vector3& force) const;

	Vector3 position() const { return _actor->getGlobalPose().p; }
	float mass() const { return _actor->getMass(); }
	Vector3 velocity() const { return _actor->getLinearVelocity(); }

	void set_linear_velocity(const Vector3& vel) const { _actor->setLinearVelocity(vel); }
	void clear_forces() const { _actor->clearForce(); }

private:
	physx::PxRigidDynamic* _actor;
	physx::PxTransform* _tr;
	RenderItem* _ri;
};

