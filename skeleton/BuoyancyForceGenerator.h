#pragma once
#include "ForceGenerator.h"
class BuoyancyForceGenerator : public ForceGenerator
{
public:
	BuoyancyForceGenerator(float maxDepth, float volume, float liquidDensity);
	~BuoyancyForceGenerator() override;
	void apply_force_particle(double t) const override;
	void apply_force_dynamics() const override;

	void update_force(Particle* particle) const;

protected:
	float _height;
	float _volume;
	float _liquidDensity;
	float _gravity;

	Particle* _particle;
};

