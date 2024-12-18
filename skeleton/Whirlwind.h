#pragma once
#include "Wind.h"
class Whirlwind : public Wind
{
public:
	Whirlwind(double k1, double k2, const physx::PxVec3& min, const physx::PxVec3& max, double K, const physx::PxVec3& pos);
	void apply_force_particle(double t) const override;

private:
	physx::PxVec3 vel_by_distance(const physx::PxVec3& pos) const;

	double _K;
	physx::PxVec3 _pos;
};

