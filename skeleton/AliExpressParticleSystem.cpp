#include "AliExpressParticleSystem.h"

#include <iostream>

#include "Particle.h"

AliExpressParticleSystem::AliExpressParticleSystem(const physx::PxVec3& pos, char t) : lifeTime_(5)
{
	tr_ = new physx::PxTransform(pos);

	switch (t)
	{
	case t == 'e':
		nx_ = std::normal_distribution<float>(50, 1);
		ny_ = std::normal_distribution<float>(0, 1);
		nz_ = std::normal_distribution<float>(0, 1);
		break;
	case t == 'f':
		nx_ = std::normal_distribution<float>(50, 1);
		ny_ = std::normal_distribution<float>(0, 1);
		nz_ = std::normal_distribution<float>(0, 1);
		break;
	case t == 'c':
		nx_ = std::normal_distribution<float>(50, 1);
		ny_ = std::normal_distribution<float>(0, 1);
		nz_ = std::normal_distribution<float>(0, 1);
	default:
		break;
	}
}

AliExpressParticleSystem::~AliExpressParticleSystem()
{
	delete tr_;
	tr_ = nullptr;

	for(auto p : particles_)
	{
		delete p;
		p = nullptr;
	}
}

void AliExpressParticleSystem::generate()
{
	Particle* particle = new Particle(tr_->p, physx::PxVec3(nx_(gen), ny_(gen) - 10, nz_(gen)), physx::PxVec3(0, -10, 0), 0.99, 7000);
	particles_.push_back(particle);
}

void AliExpressParticleSystem::update(double t)
{
	generate();

	for (auto p : particles_) p->update(t);

	for (auto p = particles_.begin(); p != particles_.end();)
	{
		if ((*p)->time_alive() >= lifeTime_)
		{
			delete *p;
			p = particles_.erase(p);
		}
		else ++p;
	}
}
