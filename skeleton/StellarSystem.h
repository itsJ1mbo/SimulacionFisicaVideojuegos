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
	double mass;
	float radius;

	AliExpressParticleSystem* ps;
};

class StellarSystem : public RigidBodySystem
{
public:
	StellarSystem(const Vector3& pos, physx::PxPhysics* p, physx::PxScene* scene, DynamicRigidBody* player);
	~StellarSystem() override;

	void update(double t) override;
	void generate() override;

private:
	Star _star;
	Gravity* _systemGravity;
	std::list<Gravity*> _planetGravities;

	DynamicRigidBody* _player;

	void set_gravities();
	void create_star();
	void create_planet(const Vector3& dis, const float r, const double m, const Vector4& color);
};

