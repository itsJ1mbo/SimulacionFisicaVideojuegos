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

	std::list<Particle*> particles() { return particles_; }

private:
	char tipo_;
	int lifeTime_;

	physx::PxTransform* tr_;
	std::list<Particle*> particles_;

	physx::PxVec3 vel_;
	int radius_;
	physx::PxVec4 color_;

	std::random_device rd{};
	std::mt19937 gen{ rd() };

	void generate();
	physx::PxVec3 vel_by_distribution();
	void particle_properties();
};

