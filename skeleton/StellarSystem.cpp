#include "StellarSystem.h"

#include <iostream>

#include "Gravity.h"
#include "DynamicRigidBody.h"
#include "StaticRigidBody.h"
#include "AliExpressParticleSystem.h"

# define M_PI 3.14159265358979323846

StellarSystem::StellarSystem(const Vector3& pos, physx::PxPhysics* p, physx::PxScene* scene, DynamicRigidBody* player) :
	RigidBodySystem(pos, p, scene),
	_star(),
	_systemGravity(nullptr),
	_player(player)
{
}

StellarSystem::~StellarSystem()
{
	delete _systemGravity;
	_systemGravity = nullptr;

	delete _star.rb;
	_star.rb = nullptr;

	for (auto s : _planetGravities)
	{
		delete s;
		s = nullptr;
	}
}

void StellarSystem::update(double t)
{
	_systemGravity->apply_force_dynamics();

	for (const auto g : _planetGravities)
	{
		g->apply_force_dynamics();
		for (const auto p : _dynamics) g->set_pos(p->position());
	}

	_star.ps->sun_particles_system(t, _star.radius + 200);
}

void StellarSystem::set_gravities()
{
	_systemGravity = new Gravity(_star.mass, Vector3(0, 0, 0));
	_systemGravity->register_rb_system(this);

	for (const auto p : _dynamics)
	{
		Gravity* g = new Gravity(p->mass(), p->position(), p, p->geometry().sphere().radius + 10);
		g->register_rb_system(this);
		_planetGravities.push_back(g);
	}
}

void StellarSystem::create_star()
{
	_star.radius = 2000;
	_star.rb = new StaticRigidBody(_scene, _physics, _tr->p, physx::PxSphereGeometry(_star.radius), Vector4(1, 0, 0, 1));
	_star.mass = 4e15;
	_star.ps = new AliExpressParticleSystem(_tr->p, 'f', 200);
}

void StellarSystem::create_planet(const Vector3& dis, const float r, const double m, const Vector4& color)
{
	double d = m /
		((4.0 / 3.0) * M_PI * std::pow(r, 3));

	physx::PxMaterial* mat = _physics->createMaterial(0.5, 0.5, 0.0);
	DynamicRigidBody* p = new DynamicRigidBody(_scene, _physics, _tr->p + dis, physx::PxSphereGeometry(r), mat, color, d, m);

	double orbitalSpeed = sqrt((G * _star.mass) / dis.magnitude());

	physx::PxVec3 tangentialVelocity = (p->position() - _star.rb->position()).getNormalized().cross(Vector3(0, 1, 0));
	tangentialVelocity.normalize();
	tangentialVelocity *= orbitalSpeed;
	p->set_linear_velocity(-tangentialVelocity);

	_dynamics.push_back(p);
}

void StellarSystem::generate()
{
	create_star();
	create_planet(Vector3(4500, 0, 0), 50, 1.47e10, Vector4(0, 1, 0, 1));
	//create_planet(Vector3(200, 0, 0), 4, 2000000, Vector4(0, 0, 1, 1));

	set_gravities();

	_dynamics.push_back(_player);
}
