#pragma once

#include <PxPhysicsAPI.h>
#include <list>
#include <random>

class SpringForceGenerator;
class AnchoredSpringFG;
class BuoyancyForceGenerator;

class Particle;

class AliExpressParticleSystem
{
public:
	AliExpressParticleSystem(const physx::PxVec3& pos, const char t = 'e');
	~AliExpressParticleSystem();

	void update(double t);

	std::list<Particle*> particles() const { return _particles; }

private:
	SpringForceGenerator* _spring1;
	SpringForceGenerator* _spring2;
	AnchoredSpringFG* _spring3;
	BuoyancyForceGenerator* _buoyancy;

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
	void generate_spring();
	void generate_buoyancy();
	void generate_anchored_spring();
	physx::PxVec3 vel_by_distribution();
	void particle_properties();
};

