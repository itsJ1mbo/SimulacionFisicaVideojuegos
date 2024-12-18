#include "Gravity.h"

#include <iostream>

#include "Particle.h"

Gravity::Gravity(const float m, const Vector3& pos) :
	_mass(m), _pos(pos)
{
}

void Gravity::apply_force_particle(double t) const
{
	for (const auto& ps : _ps) 
	{
		for (const auto& p : ps->particles()) 
		{
			const physx::PxVec3 gravityForce = p->mass() * Vector3();
			p->apply_force(gravityForce);
		}
	}
}

void Gravity::apply_force_dynamics() const
{
	for (const auto& rbs : _rbs)
	{
		for (const auto& rb : rbs->dynamics())
		{
			Vector3 r = rb->position() - _pos;
			Vector3 gravity = G * _mass / std::pow(r.magnitude(), 2) * r.getNormalized();
			const physx::PxVec3 gravityForce = gravity * rb->mass();
			rb->add_force(-gravityForce);

			std::cout << "GRAV: " << gravityForce.x << " " << gravityForce.y << " " << gravityForce.z << std::endl;
		}
	}
}
