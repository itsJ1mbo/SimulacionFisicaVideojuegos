#include "AliExpressParticleSystem.h"
#include "Particle.h"

AliExpressParticleSystem::AliExpressParticleSystem(physx::PxVec3 pos) : lifeTime_(5)
{
	tr_ = new physx::PxTransform(pos);
}

AliExpressParticleSystem::~AliExpressParticleSystem()
{
	delete tr_;
}

void AliExpressParticleSystem::generate()
{
	Particle* particle = new Particle(tr_->p, physx::PxVec3(nx_(gen), ny_(gen) - 10, nz_(gen)), 0.99, 7000);
	particles_.push_back(particle);
}

void AliExpressParticleSystem::update(double t)
{
	std::list<Particle*>::iterator p = particles_.begin();
	while (p != particles_.end())
	{
		(*p)->update(t);
		++p;
		/*if ((*p)->time_alive() == lifeTime_)
		{
			p = particles_.erase(p);
		}
		else {
			(*p)->update(t);
			++p;
		}*/
	}
}
