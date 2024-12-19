#pragma once
#include "RigidBodySystem.h"
class RocketForce;

class PlayerSystem : public RigidBodySystem
{
public:
	PlayerSystem(const Vector3& pos, physx::PxPhysics* p, physx::PxScene* scene);
	~PlayerSystem() override;

	void update(double t) override;
	void generate() override;
	void move() const;
	DynamicRigidBody* player() const { return _dynamics.back(); }
private:
	RocketForce* _rocket;
};

