#include "Gravity.h"
#include "Particle.h"

Gravity::Gravity() : gravity_(0, -9.8, 0)
{
}

void Gravity::apply_force()
{
	for (auto ps : ps_) 
	{
		for (auto p : ps->particles()) 
		{
			physx::PxVec3 gravityForce = (p->mass() * gravity_);
			p->apply_force(gravityForce);
		}
	}
}
