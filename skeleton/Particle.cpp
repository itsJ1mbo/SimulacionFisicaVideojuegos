#include "Particle.h"
#include <iostream>

Particle::Particle(physx::PxVec3 pos, physx::PxVec3 vel, double d, double m) : vel_(vel), acc_(0, 0, 0), damp_(d), mass_(m)
{
	pos_ = new physx::PxTransform(pos);

	const physx::PxSphereGeometry sphere(5);
	physx::PxShape* shape = CreateShape(sphere);

	ri_ = new RenderItem(shape, pos_, Vector4(0.75, 0.75, 0.75, 1));

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

void Particle::update(double t)
{
	integrate(t);

	lifeTime_++;
}


