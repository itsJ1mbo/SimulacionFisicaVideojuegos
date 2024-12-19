#include "AliExpressParticleSystem.h"
#include <iostream>

#include "Particle.h"
#include "Explosion.h"

AliExpressParticleSystem::AliExpressParticleSystem(const physx::PxVec3& pos, int time) :
	_lifeTime(time), _radius(0), _color(), _time(0), _total(0)
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

Vector3 AliExpressParticleSystem::pos_in_sphere(const float r)
{
	std::uniform_real_distribution<float> thetaDist(0.0, physx::PxTwoPi);
	std::uniform_real_distribution<float> phiDist(-physx::PxHalfPi, physx::PxHalfPi);

	float theta = thetaDist(_gen);
	float phi = phiDist(_gen);

	float xPos = r * cos(phi) * cos(theta);
	float yPos = r * cos(phi) * sin(theta);
	float zPos = r * sin(phi);

	return {_tr->p.x + xPos, _tr->p.y + yPos, _tr->p.z + zPos};
}

void AliExpressParticleSystem::sun_explosions_particles(const float r, double t)
{
	Vector3 pos;

	if (_time >= _total)
	{
		_exploded = true;
		_radius = 30;
		_color = { 1, 0.3f , 0, 1 };

		pos = pos_in_sphere(r);

		for (int i = 0; i < 20; ++i)
		{
			float theta = std::uniform_real_distribution<float>(0.0f, physx::PxTwoPi)(_gen);
			float phi = std::acos(std::uniform_real_distribution<float>(-1.0f, 0.0f)(_gen));

			float x = std::sin(phi) * std::cos(theta);
			float y = std::sin(phi) * std::sin(theta);
			float z = std::cos(phi);

			physx::PxVec3 direction = physx::PxVec3(x, y, z);

			std::uniform_real_distribution<float> speedDist(50.0f, 100.0f);
			float speed = speedDist(_gen);

			_vel = direction * speed;

			Particle* particle = new Particle(pos, _vel, physx::PxVec3(0, 0, 0), 0.99, 1, _color, _radius);
			_particles.push_back(particle);
		}

		std::uniform_real_distribution<> time(1, 2);
		_total = time(_gen);
		_time = 0;

		Explosion* e = new Explosion(100, pos, 1000, 2);
		e->register_particle_system(this);

	}

	update(t);

	if (_exploded)
	{
		Explosion* e = new Explosion(100, pos, 1000, 2);
		e->register_particle_system(this);
		e->apply_force_particle(t);
	}

	_time += t;
}

void AliExpressParticleSystem::sun_particles_system(const double t, const float r)
{
	_radius = 20;
	_color = { 1, 0.6f , 0, 1 };

	for (int i = 0; i < 10; ++i) 
	{
		std::uniform_real_distribution<float> x(-40, 40);
		std::uniform_real_distribution<float> y(-40, 40);
		std::uniform_real_distribution<float> z(-40, 40);
		std::uniform_real_distribution<float> speedDist(50.0f, 100.0f);

		_vel = physx::PxVec3(x(_gen), y(_gen), z(_gen)).getNormalized() * speedDist(_gen);

		Particle* particle = new Particle(pos_in_sphere(r), _vel, physx::PxVec3(0, 0, 0), 0.99, 1, _color, _radius);
		_particles.push_back(particle);
	}

	update(t);
}

void AliExpressParticleSystem::wind_planet_particles(const float r, const DynamicRigidBody* rb, const double t)
{
	_radius = 100;
	_color = { 0.75, 0.75, 0.75, 1 };
	float p = pos_in_sphere(r).magnitude();
	Vector3 rPos = rb->position() + pos_in_sphere(r);
	Particle* particle = new Particle(rPos, Vector3(0, 0, 0), physx::PxVec3(0, 0, 0), 0.99, 1, _color, _radius);
	_particles.push_back(particle);

	update(t);
}

bool AliExpressParticleSystem::check_in_sphere(const Particle* p, const float r) const
{
	return (p->position() - _tr->p).magnitude() < r;
}

void AliExpressParticleSystem::update(double t)
{
	for (auto p = _particles.begin(); p != _particles.end();)
	{
		(*p)->update(t);

		if (_lifeTime < 1000 && (*p)->time_alive() >= _lifeTime)
		{
			delete *p;
			p = _particles.erase(p);
		}
		else ++p;
	}
}
