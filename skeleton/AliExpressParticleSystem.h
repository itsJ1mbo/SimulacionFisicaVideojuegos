#pragma once

#include <PxPhysicsAPI.h>
#include <list>
#include <random>

class Particle;

class AliExpressParticleSystem
{
public:
	AliExpressParticleSystem(physx::PxVec3 pos);
	~AliExpressParticleSystem();

	void generate();
	void update(double t);

private:
	int lifeTime_;

	physx::PxTransform* tr_;
	std::list<Particle*> particles_;
	std::list<Particle*> deletions_;

	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<float> nx_{ 5.0, 1.0 };
	std::normal_distribution<float> ny_{ 2.0, 2.0 };
	std::normal_distribution<float> nz_{ 0.0, 8.0 };
};

