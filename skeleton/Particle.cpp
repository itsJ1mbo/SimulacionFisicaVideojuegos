#include "Particle.h"
#include <iostream>

Particle::Particle(const physx::PxVec3& pos, const physx::PxVec3& vel, const physx::PxVec3& acc, double d, double m) : lifeTime_(0), vel_(vel), acc_(acc), damp_(d), mass_(m)
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
	ri_ = nullptr;

	delete pos_;
	pos_ = nullptr;
}

void Particle::integrate(const double t)
{
	vel_ = vel_ * pow(damp_, t) + acc_ * t;

	pos_->p += vel_ * t;
}

void Particle::update(double t)
{
	integrate(t);

	lifeTime_ += t;
}


