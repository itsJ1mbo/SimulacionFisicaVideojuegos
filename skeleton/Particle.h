#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(physx::PxVec3 pos, physx::PxVec3 vel);
	~Particle();

	void integrate(double t);
	void accelerate(Vector3 a);

private:
	physx::PxVec3 vel_;
	physx::PxVec3 acc_;
	physx::PxTransform* pos_;
	RenderItem* ri_;
};

