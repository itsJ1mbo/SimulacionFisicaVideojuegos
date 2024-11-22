#pragma once

#include <PxPhysicsAPI.h>
#include <list>
#include <random>

class Particle;

class AliExpressParticleSystem
{
public:
	AliExpressParticleSystem(const physx::PxVec3& pos, const char t = 'e');
	~AliExpressParticleSystem();

	void update(double t);

	std::list<Particle*> particles() { return _particles; }

private:
	char _tipo;
	int _lifeTime;

	physx::PxTransform* _tr;
	std::list<Particle*> _particles;

	physx::PxVec3 _vel;
	int _radius;
	physx::PxVec4 _color;

	std::random_device _rd{};
	std::mt19937 _gen{ _rd() };

	void generate();
	physx::PxVec3 vel_by_distribution();
	void particle_properties();
};

