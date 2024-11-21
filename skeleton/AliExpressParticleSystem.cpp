#include "AliExpressParticleSystem.h"

#include <iostream>

#include "Particle.h"

AliExpressParticleSystem::AliExpressParticleSystem(const physx::PxVec3& pos, char t) : lifeTime_(19), tipo_(t), color_()
{
	tr_ = new physx::PxTransform(pos);
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
	particle_properties();
	Particle* particle = new Particle(tr_->p, vel_by_distribution(), radius_, physx::PxVec3(0, 0, 0), 0.99, 1, color_);
	particles_.push_back(particle);
}

physx::PxVec3 AliExpressParticleSystem::vel_by_distribution()
{
	if (tipo_ == 'e') {
		std::normal_distribution<float> x(50, 1);
		std::normal_distribution<float> y(10, 1);
		std::normal_distribution<float> z(10, 1);

		return physx::PxVec3(x(gen), y(gen), z(gen));
	}
	else if (tipo_ == 'f') {
		std::uniform_real_distribution<float> x(-4, 4);
		std::uniform_real_distribution<float> y(20, 40);
		std::uniform_real_distribution<float> z(-4, 4);

		return physx::PxVec3(x(gen), y(gen), z(gen));
	}
	if (tipo_ == 'n') {
		std::normal_distribution<float> x(0, 5);
		std::normal_distribution<float> y(10, 1);
		std::normal_distribution<float> z(0, 5);

		return physx::PxVec3(x(gen), y(gen), z(gen));
	}
}

void AliExpressParticleSystem::particle_properties()
{
	if (tipo_ == 'e') {
		radius_ = 5;
		color_ = { 0.75, 0.75, 0.75, 1 };
	}
	else if (tipo_ == 'f') {
		radius_ = 1;
		color_ = { 0, 0 , 1, 1 };
	}
	if (tipo_ == 'n') {
		radius_ = 5;
		color_ = { 0.75, 0.75, 0.75, 1 };
	}
}

void AliExpressParticleSystem::update(double t)
{
	generate();

	for (auto p = particles_.begin(); p != particles_.end();)
	{
		(*p)->update(t);

		if ((*p)->time_alive() >= lifeTime_)
		{
			delete *p;
			p = particles_.erase(p);
		}
		else ++p;
	}
}
