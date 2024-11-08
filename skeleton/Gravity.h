#pragma once
#include "ForceGenerator.h"
class Gravity : public ForceGenerator
{
public:
	Gravity();

	void apply_force() override;

private:
	physx::PxVec3 gravity_;
};

