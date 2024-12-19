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
	AliExpressParticleSystem(const physx::PxVec3& pos, const char t, int time);
	~AliExpressParticleSystem();

	void update(double t);


	void sun_particles_system(const double t, const float r);

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
	std::vector<Particle*> _springParticles;

	physx::PxVec3 _vel;
	float _radius;
	physx::PxVec4 _color;

	std::random_device _rd{};
	std::mt19937 _gen{ _rd() };

	void generate();
	void generate_spring();
	void generate_buoyancy();
	void generate_anchored_spring();


	bool check_in_sphere(const Particle* p, const float r) const;


	physx::PxVec3 vel_by_distribution();
	void particle_properties();
};

