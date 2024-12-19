#pragma once
#include "RigidBodySystem.h"

#include <random>

class AsteroidBeltSystem : public RigidBodySystem
{
public:
	AsteroidBeltSystem(const Vector3& center, const Vector3& plane, float min, float max, physx::PxPhysics* p, physx::PxScene* s);
	~AsteroidBeltSystem() override;

	void update(double t) override;
	void generate() override;

private:
	std::random_device _rd{};
	std::mt19937 _gen{ _rd() };

	Vector3 _plane;
	float _min;
	float _max;
};

