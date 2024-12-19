#pragma once
#include "ForceGenerator.h"
class RocketForce : public ForceGenerator
{
public:
	RocketForce(const Vector3& dir, const float f);

	void apply_force_particle(double t) const override;
	void apply_force_dynamics(double t) const override;

	void ser_dir(const Vector3& d) { _dir = d; }

private:
	Vector3 _dir;
	float _f;
};

