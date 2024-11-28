#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(const physx::PxVec3& pos, const physx::PxVec3& vel, int r, const physx::PxVec3& acc, double d, double m, physx::PxVec4 color);
	~Particle();

	void update(double t);

	double time_alive() const { return _lifeTime; }

	double mass() const { return _mass; }
	Vector3 velocity() const { return _vel; }
	Vector3 position() const { return _pos->p; }

	void apply_force(const physx::PxVec3& f) { _prevForce = f; _force += f; }

private:
	void integrate(const double t);

	double _lifeTime;

	physx::PxVec3 _vel;
	physx::PxVec3 _force;
	physx::PxVec3 _prevForce;
	physx::PxVec3 _acc;
	physx::PxTransform* _pos;

	double _damp;
	double _mass;

	RenderItem* _ri;
};

