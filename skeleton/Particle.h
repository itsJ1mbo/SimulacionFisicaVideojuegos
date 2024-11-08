#pragma once

#include <PxPhysicsAPI.h>
#include "RenderUtils.hpp"

class Particle
{
public:
	Particle(const physx::PxVec3& pos, const physx::PxVec3& vel, int r, const physx::PxVec3& acc, double d, double m, physx::PxVec4 color);
	~Particle();

	void update(double t);

	int time_alive() const { return lifeTime_; }
	double mass() { return mass_; }
	void apply_force(physx::PxVec3& f) { force_ = f; };

private:
	void integrate(const double t);

	double lifeTime_;

	physx::PxVec3 vel_;
	physx::PxVec3 force_;
	physx::PxVec3 acc_;
	physx::PxTransform* pos_;

	double damp_;
	double mass_;

	RenderItem* ri_;
};

