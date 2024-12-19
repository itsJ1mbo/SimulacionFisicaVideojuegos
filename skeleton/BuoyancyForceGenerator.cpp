#include "BuoyancyForceGenerator.h"
#include "Particle.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(DynamicRigidBody* w, const float maxDepth, const float volume, const float liquidDensity) :
	_height(maxDepth),
	_volume(volume),
	_liquidDensity(liquidDensity),
	_gravity(1.0f),
	_particle(w)
{
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
= default;

void BuoyancyForceGenerator::apply_force_particle(double t) const
{
}

void BuoyancyForceGenerator::apply_force_dynamics(double t) const
{
}

void BuoyancyForceGenerator::update_force(const DynamicRigidBody* particle) const
{
	const float h = (_particle->position() - particle->position()).magnitude();
	const float h0 = _particle->geometry().sphere().radius;

	//const Vector3 v = particle->position() - _particle->position();

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

	force = _liquidDensity * _volume * _gravity * immersed * -(_particle->position() - particle->position()).getNormalized();

	particle->add_force(force);
}
