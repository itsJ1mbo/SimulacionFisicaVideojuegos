#pragma once

#include <PxPhysicsAPI.h>
#include <list>

class Particle;

class AliExpressParticleSystem
{
public:
	AliExpressParticleSystem(physx::PxVec3 pos);
	~AliExpressParticleSystem();

	void generate();

private:
	int lifeTime_;

	physx::PxTransform* tr_;
	std::list<Particle*> particles_;
};

