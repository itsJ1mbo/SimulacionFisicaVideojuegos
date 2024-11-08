#pragma once
#include <list>
#include "AliExpressParticleSystem.h"

class ForceGenerator
{
public:
	ForceGenerator() = default;

	virtual void apply_force() = 0;
	void register_system(AliExpressParticleSystem* ps) { ps_.push_back(ps); }
protected:
	std::list<AliExpressParticleSystem*> ps_;
};

