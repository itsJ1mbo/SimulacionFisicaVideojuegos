#pragma once
#include "Wind.h"
class Whirlwind : public Wind
{
public:
	Whirlwind(double k1, double k2, const physx::PxVec3& min, const physx::PxVec3& max, double K, const physx::PxVec3& pos);

private:
	void apply_force() override;

	physx::PxVec3 vel_by_distance(const physx::PxVec3& pos);

	double _K;
	physx::PxVec3 _pos;
};

