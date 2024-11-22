#pragma once
#include "ForceGenerator.h"

class Explosion : public ForceGenerator
{
public:
	Explosion(double R, const physx::PxVec3& c, double K, double t);

	void apply_force(double t) override;

private:
	double r(const physx::PxVec3& pos) const;

	double _radius;
	physx::PxVec3 _center;

	double _K;
	double _t;

	const double E = 2.718281828459045;
};

