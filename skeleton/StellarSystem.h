#pragma once
#include "RigidBodySystem.h"

class AliExpressParticleSystem;
class DynamicRigidBody;
class StaticRigidBody;
class Gravity;
class RenderItem;

struct Star
{
	StaticRigidBody* rb;
	float mass;

	AliExpressParticleSystem* ps;
};

class StellarSystem : public RigidBodySystem
{
public:
	StellarSystem(const Vector3& pos, physx::PxPhysics* p, physx::PxScene* scene);
	~StellarSystem() override;

	void update(double t) override;

private:
	Star _star;
	Gravity* _systemGravity;
	std::list<Gravity*> _planetGravities;

	void set_gravities();
	void create_star();
	void create_planet(const Vector3& dis, const float r, const float m);
	void generate() override;
};

