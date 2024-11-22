#pragma once
#include "ForceGenerator.h"

class Wind : public ForceGenerator
{
public:
	Wind(const physx::PxVec3& vel, double k1, double k2, const physx::PxVec3& min, const physx::PxVec3& max);
	void apply_force(double t) const override;

protected:
	bool is_under_effect(const physx::PxVec3& pos) const;

	physx::PxVec3 _windVel;
	physx::PxVec3 _minZone;
	physx::PxVec3 _maxZone;

	double _k1;
	double _k2;
};