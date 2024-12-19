#include "RocketForce.h"

#include <iostream>

#include "RenderUtils.hpp"

RocketForce::RocketForce(const Vector3& dir, const float f) :
	_dir(dir),
	_f(f)
{
}

void RocketForce::apply_force_particle(double t) const
{
}

void RocketForce::apply_force_dynamics(double t) const
{
	for (const auto& rbs : _rbs)
	{
		for (const auto& rb : rbs->dynamics())
		{
			rb->add_force(_dir * _f * rb->mass());
			std::cout << "POS: " << rb->position().x << " " << rb->position().y << " " << rb->position().x << std::endl;
		}
	}
}
