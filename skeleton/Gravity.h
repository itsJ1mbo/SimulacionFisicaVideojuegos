#pragma once
#include "ForceGenerator.h"
class Gravity : public ForceGenerator
{
public:
	Gravity();

	void apply_force(double t) const override;

private:
	physx::PxVec3 _gravity;
};

