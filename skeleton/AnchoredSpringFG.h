#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringFG : public SpringForceGenerator
{
public:
	AnchoredSpringFG(double k, double l, const physx::PxVec3& anchor);

	~AnchoredSpringFG() override;
};

