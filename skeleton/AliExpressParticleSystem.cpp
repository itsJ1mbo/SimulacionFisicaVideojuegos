#include "AliExpressParticleSystem.h"
#include "Particle.h"

AliExpressParticleSystem::AliExpressParticleSystem(physx::PxVec3 pos) : lifeTime_(10)
{
	tr_ = new physx::PxTransform(pos);
}

AliExpressParticleSystem::~AliExpressParticleSystem()
{
	delete tr_;
}

void AliExpressParticleSystem::generate()
{
	//Particle* particle = new Particle(tr_->p, PxVec3(25 * GetCamera()->getDir().x, gScene->getGravity().y * GetCamera()->getDir().y, GetCamera()->getDir().z * 25), 0.99, 7000);
	//particles_.push_back(particle);
}
