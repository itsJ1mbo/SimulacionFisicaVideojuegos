#pragma once

#include <PxPhysicsAPI.h>
#include <list>
#include <random>

#include "core.hpp"

class DynamicRigidBody;
class SpringForceGenerator;
class AnchoredSpringFG;
class BuoyancyForceGenerator;

class Particle;

class AliExpressParticleSystem
{
public:
	AliExpressParticleSystem(const physx::PxVec3& pos, int time);
	~AliExpressParticleSystem();

	void sun_explosions_particles(const float r, double t);
	void sun_particles_system(const double t, const float r);
	void wind_planet_particles(const float r, const DynamicRigidBody* rb, double t);

	std::list<Particle*> particles() const { return _particles; }

private:
	int _lifeTime;

	physx::PxTransform* _tr;
	std::list<Particle*> _particles;

	physx::PxVec3 _vel;
	float _radius;
	physx::PxVec4 _color;

	std::random_device _rd{};
	std::mt19937 _gen{ _rd() };

	double _time;
	double _total;
	int _exploded;

	Vector3 pos_in_sphere(const float r);
	bool check_in_sphere(const Particle* p, const float r) const;

	void update(double t);
};

