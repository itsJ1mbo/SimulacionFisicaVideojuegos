#include "Particle.h"
#include <iostream>

Particle::Particle(physx::PxVec3 pos, physx::PxVec3 vel) : vel_(vel) 
{
	pos_ = new physx::PxTransform(pos);

	const physx::PxSphereGeometry sphere(10);
	physx::PxShape* shape = CreateShape(sphere);

	ri_ = new RenderItem(shape, pos_, Vector4(1.0, 0.0, 0.0, 1.0));

	RegisterRenderItem(ri_);
}

Particle::~Particle()
{
	delete ri_;

	DeregisterRenderItem(ri_);
}

void Particle::integrate(double t)
{
	pos_->p += vel_ * t;
}
