#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Particle
{
public:
	Ground g;

	Particle(const physx::PxVec3& pos, const physx::PxVec3& vel, const physx::PxVec3& acc, double d, double m, const physx::PxVec4& color, float r);
	Particle(const physx::PxVec3& pos, double d, double m, physx::PxVec4 color, double x, double y, double z);
	~Particle();

	void update(double t);

	double time_alive() const { return _lifeTime; }

	double mass() const { return _mass; }
	Vector3 velocity() const { return _vel; }
	Vector3 position() const { return _pos->p; }
	physx::PxGeometryHolder geometry() const { return _shape->getGeometry(); }

	void apply_force(const physx::PxVec3& f) { _force += f; }

private:
	void integrate(const double t);

	double _lifeTime;

	physx::PxVec3 _vel;
	physx::PxVec3 _force;
	physx::PxVec3 _prevForce;
	physx::PxVec3 _acc;
	physx::PxTransform* _pos;
	physx::PxShape* _shape;

	double _damp;
	double _mass;

	RenderItem* _ri;
};

