#pragma once

#include <PxPhysicsAPI.h>
#include <list>
#include <random>

class Particle;

class AliExpressParticleSystem
{
public:
	AliExpressParticleSystem(const physx::PxVec3& pos, char t = 'e');
	~AliExpressParticleSystem();

	void update(double t);

private:
	int lifeTime_;

	physx::PxTransform* tr_;
	std::list<Particle*> particles_;

	std::random_device rd{};
	std::mt19937 gen{ rd() };
	std::normal_distribution<float> nx_;
	std::normal_distribution<float> ny_;
	std::normal_distribution<float> nz_;

	void generate();
};

