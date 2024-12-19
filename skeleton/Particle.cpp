#include "Particle.h"
#include <iostream>

Particle::Particle(const physx::PxVec3& pos, const physx::PxVec3& vel, const physx::PxVec3& acc, double d, double m, const physx::PxVec4& color, const float r) :
	g(),
	_lifeTime(0), _vel(vel), _force(0, 0, 0), _acc(acc), _damp(d), _mass(m)
{
	_pos = new physx::PxTransform(pos);

	_shape = CreateShape(physx::PxSphereGeometry(r));

	_ri = new RenderItem(_shape, _pos, color);
}

Particle::Particle(const physx::PxVec3& pos, double d, double m, physx::PxVec4 color, double x, double y, double z) :
	g(),
	_lifeTime(0), _vel(Vector3()), _force(0, 0, 0), _acc(Vector3()), _damp(d), _mass(m)
{
	_pos = new physx::PxTransform(pos);

	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(x, y, z));

	_ri = new RenderItem(shape, _pos, color);
}

Particle::~Particle()
{
	DeregisterRenderItem(_ri);
	_ri = nullptr;

	delete _pos;
	_pos = nullptr;

	_shape->release();
	_shape = nullptr;
}

void Particle::integrate(const double t)
{
	_acc = _force / _mass;

	_vel = _vel * pow(_damp, t) + _acc * t;

	_pos->p += _vel * t;

	_force = Vector3(0, 0, 0);
}

void Particle::update(const double t)
{
	integrate(t);

	_lifeTime += t;
}


