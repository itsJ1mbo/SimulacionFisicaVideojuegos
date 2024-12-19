#include "Gravity.h"

#include <iostream>

#include "Particle.h"

Gravity::Gravity(const double m, const Vector3& pos, DynamicRigidBody* origin, Particle* p, const float r) :
	_mass(m), _pos(pos), _extraR(r), _origin(origin), _particle(p)
{
}

void Gravity::apply_force_particle(double t) const
{
	for (const auto& ps : _ps) 
	{
		for (const auto& p : ps->particles()) 
		{
			if (_particle != p && p != nullptr)
			{
				Vector3 pos = p->position();
				Vector3 oPos = _pos;
				if (_particle != nullptr) oPos = _particle->position();

				Vector3 r = pos - oPos;
				float mag = r.magnitude();

				Vector3 gravity = G * _mass / std::pow(mag, 2) * r.getNormalized();
				physx::PxVec3 gravityForce = gravity * p->mass();

				if (mag < _extraR)
				{
					p->g.grounded = true;
					p->g.position = oPos;
					gravityForce = Vector3(gravityForce.x * 10000, gravityForce.y * 10000, gravityForce.z * 10000);
				}
				p->apply_force(-gravityForce);
			}
		}
	}
}

void Gravity::apply_force_dynamics(double t) const
{
	for (const auto& rbs : _rbs)
	{
		for (const auto& rb : rbs->dynamics())
		{
			if (_origin != rb && rb != nullptr)
			{
				Vector3 pos = rb->position();
				Vector3 oPos = _pos;
				if (_origin != nullptr) oPos = _origin->position();

				Vector3 r = pos - oPos;
				float mag = r.magnitude();

				Vector3 gravity = G * _mass / std::pow(mag, 2) * r.getNormalized();
				physx::PxVec3 gravityForce = gravity * rb->mass();

				if (mag < _extraR) 
				{
					rb->g.grounded = true;
					rb->g.position = oPos;
					gravityForce = Vector3(gravityForce.x * 1000, gravityForce.y * 1000, gravityForce.z * 1000);
				}
				rb->add_force(-gravityForce);
			}
		}
	}
}
