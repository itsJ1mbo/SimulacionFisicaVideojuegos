#include "Particle.h"
#include <iostream>

Particle::Particle(physx::PxVec3 pos, physx::PxVec3 acc, double d, double m) : vel_(0, 0, 0), acc_(acc), damp_(d), mass_(m)
{
	pos_ = new physx::PxTransform(pos);

	const physx::PxSphereGeometry sphere(10);
	physx::PxShape* shape = CreateShape(sphere);

	ri_ = new RenderItem(shape, pos_, Vector4(1.0, 0.0, 0.0, 1.0));

	RegisterRenderItem(ri_);
}

Particle::~Particle()
{
	DeregisterRenderItem(ri_);

	delete ri_;
	delete pos_;
}

void Particle::integrate(const double t)
{
	vel_ = vel_ * pow(damp_, t) + acc_ * t;

	pos_->p += vel_ * t;
}

void Particle::accelerate(const Vector3& a)
{
	acc_ = a;
}


