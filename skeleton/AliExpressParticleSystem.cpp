#include "AliExpressParticleSystem.h"
#include "SpringForceGenerator.h"
#include <iostream>

#include "AnchoredSpringFG.h"
#include "Particle.h"

AliExpressParticleSystem::AliExpressParticleSystem(const physx::PxVec3& pos, const char t) :
	_spring1(nullptr), _spring2(nullptr), _spring3(nullptr), _tipo(t), _lifeTime(100), _radius(0), _color()
{
	_tr = new physx::PxTransform(pos);
	if (_tipo == 'm')
	{
		generate_spring();
		generate_anchored_spring();
	}
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

void AliExpressParticleSystem::generate_spring()
{
	particle_properties();

	Particle* particle1 = new Particle(_tr->p + Vector3(0, -10, 0), Vector3(0, 0, 0), _radius, physx::PxVec3(0, 0, 0), 0.99, 1, _color);
	Particle* particle2 = new Particle(_tr->p + Vector3(0, -10, 0), Vector3(0, 0, 0), _radius, physx::PxVec3(0, 0, 0), 0.99, 1, _color);

	_spring1 = new SpringForceGenerator(200, 10, particle2);
	_spring2 = new SpringForceGenerator(30, 10, particle1);

	_particles.push_back(particle1);
	_particles.push_back(particle2);

	_spring1->register_system(this);
	_spring2->register_system(this);
}

void AliExpressParticleSystem::generate_anchored_spring()
{
	particle_properties();

	Particle* particle3 = new Particle(_tr->p + Vector3(0, -10, 0), Vector3(0, 0, 0), _radius, physx::PxVec3(0, 0, 0), 0.99, 1, _color);
	_spring3 = new AnchoredSpringFG(1000, 10, Vector3(0, 10, 0));
	_particles.push_back(particle3);
	_spring3->register_system(this);
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
	else if (_tipo == 'n') {
		_radius = 5;
		_color = { 0.75, 0.75, 0.75, 1 };
	}
	else if (_tipo == 'm')
	{
		_radius = 5;
		_color = { 0.75, 0.75, 0.75, 1 };
	}
}

void AliExpressParticleSystem::update(double t)
{
	if (_tipo != 'm') generate();
	else if (_tipo == 'm')
	{
		if (_spring1 != nullptr) _spring1->apply_force(t);
		if (_spring2 != nullptr) _spring2->apply_force(t);
		if (_spring3 != nullptr) _spring3->apply_force(t);
	}

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
