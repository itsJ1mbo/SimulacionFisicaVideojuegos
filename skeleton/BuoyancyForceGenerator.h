#pragma once
#include "ForceGenerator.h"
class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(DynamicRigidBody* w, float maxDepth, float volume, float liquidDensity);
	~BuoyancyForceGenerator() override;
	void apply_force_particle(double t) const override;
	void apply_force_dynamics(double t) const override;

	void update_force(const DynamicRigidBody* particle) const;

protected:
	float _height;
	float _volume;
	float _liquidDensity;
	float _gravity;

	DynamicRigidBody* _particle;
};

