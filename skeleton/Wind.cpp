#include "Wind.h"
#include "Particle.h"

Wind::Wind(DynamicRigidBody* rb, const physx::PxVec3& vel, double k1, double k2, float min, float max) :
	_rb(rb),
	_windVel(vel), _minZone(min), _maxZone(max), _k1(k1), _k2(k2)
{
}

void Wind::apply_force_particle(double t) const
{
	for (const auto ps : _ps)
	{
		for (const auto p : ps->particles())
		{
			if(is_under_effect(p->position())) 
			{
				const physx::PxVec3 diffVel = _windVel - p->velocity();
				const double magnitude = diffVel.magnitude();
				const physx::PxVec3 windForce = (_k1 * diffVel + _k2 * magnitude * diffVel) * magnitude;

				p->apply_force(windForce);
			}
		}
	}
}

void Wind::apply_force_dynamics(double t) const
{
	for (const auto rbs : _rbs)
	{
		for (const auto rb : rbs->dynamics())
		{
			if (is_under_effect(rb->position()))
			{
				const physx::PxVec3 diffVel = _windVel - rb->velocity();
				const double magnitude = diffVel.magnitude();
				const physx::PxVec3 windForce = (_k1 * diffVel + _k2 * magnitude * diffVel) * magnitude;

				rb->add_force(windForce);
			}
		}
	}
}

bool Wind::is_under_effect(const physx::PxVec3& pos) const
{
	float r = (pos - _rb->position()).magnitude();

	return r >= _minZone && r <= _maxZone;
}
