#pragma once
#include "ForceGenerator.h"

constexpr float G = 6.67430e-11f;

class Gravity : public ForceGenerator
{
public:
	Gravity(const float m, const Vector3& pos);

	void apply_force_particle(double t) const override;
	void apply_force_dynamics() const override;

private:
	float _mass;
	Vector3 _pos;
};

