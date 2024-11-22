#include "Particle.h"
#include <iostream>

Particle::Particle(const physx::PxVec3& pos, const physx::PxVec3& vel, int r, const physx::PxVec3& acc, double d, double m, physx::PxVec4 color) : 
	_lifeTime(0), _vel(vel), _force(0, 0, 0), _acc(acc), _damp(d), _mass(m)
{
	_pos = new physx::PxTransform(pos);

	const physx::PxSphereGeometry sphere(r);
	physx::PxShape* shape = CreateShape(sphere);

	_ri = new RenderItem(shape, _pos, color);
}

Particle::~Particle()
{
	DeregisterRenderItem(_ri);
	_ri = nullptr;

	delete _pos;
	_pos = nullptr;
}

void Particle::integrate(const double t)
{
	_acc = _force / _mass;

	_vel = _vel * pow(_damp, t) + _acc * t;

	_pos->p += _vel * t;
}

void Particle::update(const double t)
{
	integrate(t);

	_lifeTime += t;
}


