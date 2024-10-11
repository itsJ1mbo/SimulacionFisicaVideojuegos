#include "Particle.h"
#include <iostream>

Particle::Particle(physx::PxVec3 pos, physx::PxVec3 vel) : vel_(0, 0, 0), acc_(vel) 
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
	vel_ = acc_ * t;
	pos_->p += vel_ * t;

	std::cout << acc_.x << std::endl;
}

void Particle::accelerate(Vector3 a)
{
	acc_ = a;
	std::cout << acc_.x << std::endl;
}


