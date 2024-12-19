#pragma once
#include "ForceGenerator.h"

class Wind : public ForceGenerator
{
public:
	Wind(DynamicRigidBody* rb, const physx::PxVec3& vel, double k1, double k2, float min, float max);
	void apply_force_particle(double t) const override;
	void apply_force_dynamics(double t) const override;
protected:
	bool is_under_effect(const physx::PxVec3& pos) const;

	DynamicRigidBody* _rb;
	physx::PxVec3 _windVel;
	float _minZone;
	float _maxZone;

	double _k1;
	double _k2;
};