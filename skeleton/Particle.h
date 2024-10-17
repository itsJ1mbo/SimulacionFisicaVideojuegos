#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(physx::PxVec3 pos, physx::PxVec3 acc, double d, double m);
	~Particle();

	void integrate(const double t);
	void accelerate(const Vector3& a);

private:
	physx::PxVec3 vel_;
	physx::PxVec3 acc_;
	physx::PxTransform* pos_;

	double damp_;
	double mass_;

	RenderItem* ri_;
};

