#include "SpringForceGenerator.h"
#include "Particle.h"
#include "core.hpp"

SpringForceGenerator::SpringForceGenerator(double k, double l, Particle* other) :
	_k(k), _length(l), _other(other)
{
}

void SpringForceGenerator::update_force(Particle* particle) const
{
	if (_other != nullptr && particle != nullptr)
	{
		Vector3 relativePos = _other->position() - particle->position();
		Vector3 force = Vector3(0, 0, 0);

		const float length = relativePos.normalize();
		const float dX = length - _length;

		force = relativePos * _k * dX;

		particle->apply_force(force);
	}
}

void SpringForceGenerator::apply_force(double t) const
{
	for (const auto& ps : _ps)
	{
		for (const auto& p : ps->particles())
		{
			if (p != _other) update_force(p);
		}
	}
}
