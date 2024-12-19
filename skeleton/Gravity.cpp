#include "Gravity.h"

#include <iostream>

#include "Particle.h"

Gravity::Gravity(const float m, const Vector3& pos, DynamicRigidBody* origin, const float r) :
	_mass(m), _pos(pos), _extraR(r), _origin(origin)
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
			if (_origin != rb)
			{
				Vector3 pos = rb->position();
				Vector3 oPos = _pos;
				if (_origin != nullptr) oPos = _origin->position();

				Vector3 r = pos - oPos;
				float mag = r.magnitude();

				Vector3 gravity = G * _mass / std::pow(mag, 2) * r.getNormalized();
				physx::PxVec3 gravityForce = gravity * rb->mass();

				if (mag < _extraR) gravityForce = Vector3(gravityForce.x * 1000, gravityForce.y * 1000, gravityForce.z * 1000);
				rb->add_force(-gravityForce);
			}
		}
	}
}
