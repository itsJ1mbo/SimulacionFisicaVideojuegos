#include "Gravity.h"
#include "Particle.h"

Gravity::Gravity() : _gravity(0, -9.8f, 0)
{
}

void Gravity::apply_force(double t)
{
	for (const auto ps : _ps) 
	{
		for (const auto p : ps->particles()) 
		{
			const physx::PxVec3 gravityForce = p->mass() * _gravity;
			p->apply_force(gravityForce);
		}
	}
}
