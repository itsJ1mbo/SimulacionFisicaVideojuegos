#include "StellarSystem.h"

#include <iostream>

#include "Gravity.h"
#include "DynamicRigidBody.h"
#include "StaticRigidBody.h"
#include "AliExpressParticleSystem.h"

# define M_PI 3.14159265358979323846

StellarSystem::StellarSystem(const Vector3& pos, physx::PxPhysics* p, physx::PxScene* scene) :
	RigidBodySystem(pos, p, scene)
{
	create_star();
	generate();

	set_gravities();
}

StellarSystem::~StellarSystem()
{
	delete _systemGravity;
	_systemGravity = nullptr;

	delete _star.rb;
	_star.rb = nullptr;
}

void StellarSystem::update(double t)
{
	_systemGravity->apply_force_dynamics();

	for (const auto g : _planetGravities)
	{
		g->apply_force_dynamics();
	}

	_star.ps->update(t);
}

void StellarSystem::set_gravities()
{
	_systemGravity = new Gravity(_star.mass, Vector3(0, 0, 0));
	_systemGravity->register_rb_system(this);

	for (const auto p : _dynamics)
	{
		Gravity* g = new Gravity(p->mass(), p->position());
		g->register_rb_system(this);
		_planetGravities.push_back(g);
	}
}

void StellarSystem::create_star()
{
	_star.rb = new StaticRigidBody(_scene, _physics, _tr->p, physx::PxSphereGeometry(20), Vector4(1, 0, 0, 1));
	_star.mass = 4e10;
	_star.ps = new AliExpressParticleSystem(_tr->p, 'f', 4);
}

void StellarSystem::create_planet(const Vector3& dis, const float r, const float m)
{
	float d = m /
		((4 / 3) * M_PI * std::pow(r, 3));

	DynamicRigidBody* p = new DynamicRigidBody(_scene, _physics, _tr->p + dis, physx::PxSphereGeometry(r), Vector4(1, 1, 1, 1), d);

	float orbitalSpeed = sqrt((G * _star.mass) / dis.magnitude());

	physx::PxVec3 tangentialVelocity = (p->position() - _star.rb->position()).getNormalized().cross(Vector3(0, 1, 0));
	tangentialVelocity.normalize();
	tangentialVelocity *= orbitalSpeed;
	p->set_linear_velocity(-tangentialVelocity);

	_dynamics.push_back(p);
}

void StellarSystem::generate()
{
	create_planet(Vector3(40, 0, 0), 4, 40);
	create_planet(Vector3(80, 0, 0), 4, 20000);
}
