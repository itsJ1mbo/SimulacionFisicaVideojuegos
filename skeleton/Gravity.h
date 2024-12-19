#pragma once
#include "ForceGenerator.h"

constexpr float G = 6.67430e-11f;

class Gravity : public ForceGenerator
{
public:
	Gravity(const double m, const Vector3& pos, DynamicRigidBody* origin = nullptr, Particle* p = nullptr, float r = 0);

	void apply_force_particle(double t) const override;
	void apply_force_dynamics(double t) const override;

	void set_pos(const Vector3& p) { _pos = p; }

private:
	float _mass;
	Vector3 _pos;
	float _extraR;
	DynamicRigidBody* _origin;
	Particle* _particle;
};

