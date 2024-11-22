#pragma once
#include <list>
#include "AliExpressParticleSystem.h"

class ForceGenerator
{
public:
	virtual ~ForceGenerator() = default;
	ForceGenerator() = default;

	virtual void apply_force() = 0;
	void register_system(AliExpressParticleSystem* ps) { _ps.push_back(ps); }
protected:
	std::list<AliExpressParticleSystem*> _ps;
};

