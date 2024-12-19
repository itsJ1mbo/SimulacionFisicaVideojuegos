#include "StellarSystem.h"

#include <iostream>

#include "Gravity.h"
#include "DynamicRigidBody.h"
#include "StaticRigidBody.h"
#include "AliExpressParticleSystem.h"
#include "BuoyancyForceGenerator.h"
#include "Particle.h"

StellarSystem::StellarSystem(const Vector3& pos, physx::PxPhysics* p, physx::PxScene* scene, DynamicRigidBody* player) :
	RigidBodySystem(pos, p, scene),
	_star(),
	_systemGravity(nullptr),
	_buoyancy(nullptr),
	_water(nullptr),
	_waterTr(nullptr),
	_player(player)
{
}

StellarSystem::~StellarSystem()
{
	delete _systemGravity;
	_systemGravity = nullptr;

	delete _buoyancy;
	_buoyancy = nullptr;

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
	_systemGravity->apply_force_dynamics(t);

	for (const auto g : _planetGravities)
	{
		g->apply_force_dynamics(t);
		for (const auto p : _dynamics) g->set_pos(p->position());
	}

	if (_player != nullptr) _buoyancy->update_force(_player); 

	_waterTr->p = _water->position();

	_star.ps->sun_particles_system(t, _star.radius + 150);

	_star.ps->sun_explosions_particles(_star.radius + 350, t);
}

void StellarSystem::set_gravities()
{
	_systemGravity = new Gravity(_star.mass, Vector3(0, 0, 0));
	_systemGravity->register_rb_system(this);

	for (const auto p : _dynamics)
	{
		Gravity* g = new Gravity(p->mass(), p->position(), p, nullptr, p->geometry().sphere().radius + 200);
		g->register_rb_system(this);
		_planetGravities.push_back(g);
	}
}

void StellarSystem::create_star()
{
	_star.radius = 2000;
	_star.rb = new StaticRigidBody(_scene, _physics, _tr->p, physx::PxSphereGeometry(_star.radius), Vector4(1, 0, 0, 1));
	_star.mass = 4e15;
	_star.ps = new AliExpressParticleSystem(_tr->p, 10);
	_star.exploded = false;
}	

DynamicRigidBody* StellarSystem::create_planet(const Vector3& dis, const float r, const double m, const Vector4& color)
{
	double d = m /
		((4.0 / 3.0) * physx::PxPi * std::pow(r, 3));

	physx::PxMaterial* mat = _physics->createMaterial(0.5, 0.5, 0.0);
	DynamicRigidBody* p = new DynamicRigidBody(_scene, _physics, _tr->p + dis, physx::PxSphereGeometry(r), mat, color, d, m);

	double orbitalSpeed = sqrt((G * _star.mass) / dis.magnitude());

	physx::PxVec3 tangentialVelocity = (p->position() - _star.rb->position()).getNormalized().cross(Vector3(0, 1, 0));
	tangentialVelocity.normalize();
	tangentialVelocity *= orbitalSpeed;
	p->set_linear_velocity(-tangentialVelocity);

	_dynamics.push_back(p);

	return p;
}

void StellarSystem::generate()
{
	create_star();
	create_planet(Vector3(4500, 0, 0), 50, 1.47e10, Vector4(0, 1, 0, 1));
	_water = create_planet(Vector3(7000, 0, 0), 200, 2.47e10, Vector4(0, 0, 1, 1));
	_buoyancy = new BuoyancyForceGenerator(_water, 90, 950.0f, 1000);
	_waterTr = new physx::PxTransform(_water->position());
	RenderItem* ri = new RenderItem(CreateShape(physx::PxSphereGeometry(250)), _waterTr, Vector4(0, 0, 1, 1));
	create_planet(Vector3(10000, 0, 0), 25, 3e10, Vector4(1.0f, 0.4f, 0.7f, 1.0f));

	_buoyancy->register_rb_system(this);
	set_gravities();
}

