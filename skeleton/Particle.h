#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(physx::PxVec3 pos, physx::PxVec3 vel, double d, double m);
	~Particle();

	void integrate(const double t);
	void update(double t);

	int time_alive() const { return lifeTime_; }

private:
	int lifeTime_ = 0;

	physx::PxVec3 vel_;
	physx::PxVec3 acc_;
	physx::PxTransform* pos_;

	double damp_;
	double mass_;

	RenderItem* ri_;
};

