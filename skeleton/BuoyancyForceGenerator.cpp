#include "BuoyancyForceGenerator.h"
#include "Particle.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(const float maxDepth, const float volume, const float liquidDensity) :
	_height(maxDepth),
	_volume(volume),
	_liquidDensity(liquidDensity),
	_gravity(1.0f)
{
	_particle = new Particle(Vector3(0, 0, 0), 0.99, 1, Vector4(0, 0, 1, 1), 20, 1, 20);
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
	delete _particle;
	_particle = nullptr;
}

void BuoyancyForceGenerator::apply_force(double t) const
{
}

void BuoyancyForceGenerator::update_force(Particle* particle) const
{
	const float h = particle->position().y;
	const float h0 = _particle->position().y;

	Vector3 force = Vector3(0, 0, 0);
	float immersed = 0.0f;

	if (h - h0 > _height * 0.5)
	{
		immersed = 0.0;
	}
	else if (h0 - h > _height * 0.5)
	{
		immersed = 1.0;
	}
	else
	{
		immersed = (h0 - h) / _height + 0.5;
	}

	force.y = _liquidDensity * _volume * _gravity * immersed;

	particle->apply_force(force);
}
