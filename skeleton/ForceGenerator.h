#pragma once
#include <list>
#include "AliExpressParticleSystem.h"
#include "RigidBodySystem.h"

class ForceGenerator
{
public:
	ForceGenerator() = default;
	virtual ~ForceGenerator() = default;

	virtual void apply_force_particle(double t) const = 0;
	void register_particle_system(AliExpressParticleSystem* ps) { _ps.push_back(ps); }

	virtual void apply_force_dynamics(double t) const = 0;
	void register_rb_system(RigidBodySystem* rbs) { _rbs.push_back(rbs); }
protected:
	std::list<AliExpressParticleSystem*> _ps;
	std::list<RigidBodySystem*> _rbs;
};

