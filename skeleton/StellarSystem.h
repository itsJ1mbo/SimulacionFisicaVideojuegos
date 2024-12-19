#pragma once
#include <random>

#include "RigidBodySystem.h"

class Wind;
class AsteroidBeltSystem;
class Explosion;
class BuoyancyForceGenerator;
class AliExpressParticleSystem;
class DynamicRigidBody;
class StaticRigidBody;
class Gravity;
class RenderItem;

struct Star
{
	StaticRigidBody* rb;
	double mass;
	float radius;
	bool exploded;

	Explosion* ex;
	AliExpressParticleSystem* ps;
};

class StellarSystem : public RigidBodySystem
{
public:
	StellarSystem(const Vector3& pos, physx::PxPhysics* p, physx::PxScene* scene, DynamicRigidBody* player);
	~StellarSystem() override;

	void update(double t) override;
	void generate() override;
	void set_player(DynamicRigidBody* p)
	{
		_player = p;
		_dynamics.push_back(_player);
	}

private:
	Star _star;
	Gravity* _systemGravity;
	std::list<Gravity*> _planetGravities;
	BuoyancyForceGenerator* _buoyancy;
	Wind* _wind;

	DynamicRigidBody* _water;
	physx::PxTransform* _waterTr;
	DynamicRigidBody* _player;
	AliExpressParticleSystem* _windPs;
	DynamicRigidBody* _windPlanet;

	AsteroidBeltSystem* _asteroidBelt;

	void set_gravities();
	void create_star();
	DynamicRigidBody* create_planet(const float a, const float b, const float r, const double m, const Vector4& color);
	void create_satelite(const float a, const float b, const float r, const double m, const Vector4& color, DynamicRigidBody* rb);
};

