#include "AliExpressParticleSystem.h"

#include <iostream>

#include "Particle.h"

AliExpressParticleSystem::AliExpressParticleSystem(const physx::PxVec3& pos, const char t) :
	_tipo(t), _lifeTime(19), _radius(0), _color()
{
	_tr = new physx::PxTransform(pos);
}

AliExpressParticleSystem::~AliExpressParticleSystem()
{
	delete _tr;
	_tr = nullptr;

	for(auto p : _particles)
	{
		delete p;
		p = nullptr;
	}
}

void AliExpressParticleSystem::generate()
{
	particle_properties();
	Particle* particle = new Particle(_tr->p, vel_by_distribution(), _radius, physx::PxVec3(0, 0, 0), 0.99, 1, _color);
	_particles.push_back(particle);
}

physx::PxVec3 AliExpressParticleSystem::vel_by_distribution()
{
	if (_tipo == 'e') {
		std::normal_distribution<float> x(50, 1);
		std::normal_distribution<float> y(10, 1);
		std::normal_distribution<float> z(10, 1);

		return physx::PxVec3(x(_gen), y(_gen), z(_gen));
	}
	else if (_tipo == 'f') {
		std::uniform_real_distribution<float> x(-4, 4);
		std::uniform_real_distribution<float> y(20, 40);
		std::uniform_real_distribution<float> z(-4, 4);

		return physx::PxVec3(x(_gen), y(_gen), z(_gen));
	}
	else if (_tipo == 'n') {
		std::normal_distribution<float> x(0, 5);
		std::normal_distribution<float> y(10, 1);
		std::normal_distribution<float> z(0, 5);

		return physx::PxVec3(x(_gen), y(_gen), z(_gen));
	}
	else return {};
}

void AliExpressParticleSystem::particle_properties()
{
	if (_tipo == 'e') {
		_radius = 5;
		_color = { 0.75, 0.75, 0.75, 1 };
	}
	else if (_tipo == 'f') {
		_radius = 1;
		_color = { 0, 0 , 1, 1 };
	}
	if (_tipo == 'n') {
		_radius = 5;
		_color = { 0.75, 0.75, 0.75, 1 };
	}
}

void AliExpressParticleSystem::update(double t)
{
	generate();

	for (auto p = _particles.begin(); p != _particles.end();)
	{
		(*p)->update(t);

		if ((*p)->time_alive() >= _lifeTime)
		{
			delete *p;
			p = _particles.erase(p);
		}
		else ++p;
	}
}
