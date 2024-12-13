#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double k, double l, const physx::PxVec3& anchor) :
	SpringForceGenerator(k, l, nullptr)
{
	_other = new Particle(anchor, physx::PxVec3(0, 0, 0), physx::PxVec3(0, 0, 0), 0, 0, physx::PxVec4(0, 0, 0, 0));
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete _other;
	_other = nullptr;
}
