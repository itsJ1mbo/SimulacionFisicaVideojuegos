#pragma once
#include "core.hpp"
#include "RenderUtils.hpp"

class DynamicRigidBody
{
public:
	Ground g;

	DynamicRigidBody(physx::PxScene* scene, physx::PxPhysics* physics, const Vector3& pos, const physx::PxGeometry& geometry, 
		const physx::PxMaterial* mat,
		const Vector4& color, 
		double d, const double m);
	~DynamicRigidBody();

	void add_force(const Vector3& force) const;

	physx::PxVec3 position() const { return _actor->getGlobalPose().p; }
	float mass() const { return _actor->getMass(); }
	Vector3 velocity() const { return _actor->getLinearVelocity(); }
	physx::PxGeometryHolder geometry() const { return _shape->getGeometry(); }

	void set_linear_velocity(const Vector3& vel) const { _actor->setLinearVelocity(vel); }
	void clear_forces() const { _actor->clearForce(); }

private:
	physx::PxRigidDynamic* _actor;
	physx::PxTransform* _tr;
	RenderItem* _ri;
	physx::PxShape* _shape;
};

