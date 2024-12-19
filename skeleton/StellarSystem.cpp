#include "StellarSystem.h"

#include <iostream>

#include "Gravity.h"
#include "DynamicRigidBody.h"
#include "StaticRigidBody.h"
#include "AliExpressParticleSystem.h"
#include "AsteroidBeltSystem.h"
#include "BuoyancyForceGenerator.h"
#include "Particle.h"
#include "Wind.h"

StellarSystem::StellarSystem(const Vector3& pos, physx::PxPhysics* p, physx::PxScene* scene, DynamicRigidBody* player) :
	RigidBodySystem(pos, p, scene),
	_star(),
	_systemGravity(nullptr),
	_buoyancy(nullptr),
	_wind(nullptr),
	_water(nullptr),
	_waterTr(nullptr),
	_player(player),
	_windPs(nullptr),
	_windPlanet(nullptr),
	_asteroidBelt(nullptr)
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

	delete _water;
	_water = nullptr;

	delete _waterTr;
	_waterTr = nullptr;

	delete _wind;
	_wind = nullptr;

	delete _asteroidBelt;
	_asteroidBelt = nullptr;

	delete _windPs;
	_windPs = nullptr;

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

	_wind->apply_force_dynamics(t);

	if (_player != nullptr) _buoyancy->update_force(_player); 

	_waterTr->p = _water->position();

	_star.ps->sun_particles_system(t, _star.radius - 100);

	_star.ps->sun_explosions_particles(_star.radius, t);

	_windPs->wind_planet_particles(500, _windPlanet, t);
}

void StellarSystem::set_gravities()
{
	_systemGravity = new Gravity(_star.mass, Vector3(0, 0, 0));
	_systemGravity->register_rb_system(this);
	_systemGravity->register_rb_system(_asteroidBelt);

	for (const auto p : _dynamics)
	{
		Gravity* g = new Gravity(p->mass(), p->position(), p, nullptr, p->geometry().sphere().radius + 200);
		g->register_rb_system(this);
		g->register_rb_system(_asteroidBelt);
		_planetGravities.push_back(g);
	}
}

void StellarSystem::create_star()
{
	_star.radius = 2000;
	_star.rb = new StaticRigidBody(_scene, _physics, _tr->p, physx::PxSphereGeometry(_star.radius), Vector4(1, 0, 0, 1));
	_star.mass = 4e15;
	_star.ps = new AliExpressParticleSystem(_tr->p, 5);
	_star.exploded = false;
}	

DynamicRigidBody* StellarSystem::create_planet(const float a, const float b, const float r, const double m, const Vector4& color)
{
	double d = m /
		((4.0 / 3.0) * physx::PxPi * std::pow(r, 3));

	physx::PxVec3 orbitPos = _star.rb->position() + physx::PxVec3(a * cos(0), 0.0, b * sin(0));

	physx::PxMaterial* mat = _physics->createMaterial(0.5, 0.5, 0.0);
	DynamicRigidBody* p = new DynamicRigidBody(_scene, _physics, orbitPos, physx::PxSphereGeometry(r), mat, color, d, m);

	double eR = (orbitPos - _star.rb->position()).magnitude();

	double orbitalSpeed = sqrt((G * _star.mass) * (2.0 / eR - 1.0 / a));

	physx::PxVec3 radialDirection = (orbitPos - _star.rb->position()).getNormalized();
	physx::PxVec3 tangentialVelocity = radialDirection.cross(physx::PxVec3(0, 1, 0));
	tangentialVelocity.normalize();
	tangentialVelocity *= orbitalSpeed;

	p->set_linear_velocity(-tangentialVelocity);

	_dynamics.push_back(p);

	return p;
}

void StellarSystem::create_satelite(const float a, const float b, const float r, const double m, const Vector4& color, DynamicRigidBody* rb)
{
	double d = m /
		((4.0 / 3.0) * physx::PxPi * std::pow(r, 3));

	physx::PxVec3 orbitPos = rb->position() + physx::PxVec3(a * cos(0), 0.0, b * sin(0));

	physx::PxMaterial* mat = _physics->createMaterial(0.5, 0.5, 0.0);
	DynamicRigidBody* p = new DynamicRigidBody(_scene, _physics, orbitPos, physx::PxSphereGeometry(r), mat, color, d, m);

	double eR = (orbitPos - rb->position()).magnitude();

	double orbitalSpeed = sqrt((G * rb->mass()) * (2.0 / eR - 1.0 / a));

	physx::PxVec3 radialDirection = (orbitPos - rb->position()).getNormalized();
	physx::PxVec3 tangentialVelocity = radialDirection.cross(physx::PxVec3(0, 1, 0));
	tangentialVelocity.normalize();
	tangentialVelocity *= orbitalSpeed;

	p->set_linear_velocity(-tangentialVelocity + rb->velocity());

	_dynamics.push_back(p);
}

void StellarSystem::generate()
{

	create_star();

#pragma region Gea y Urano
	create_satelite(80, 75, 10, 2e5, Vector4(0.2f, 0.2f, 1, 1), create_planet(4500, 3000, 50, 1.47e10, Vector4(0, 1, 0, 1)));
#pragma endregion

#pragma region Fontaine
	_water = create_planet(7000, 2000, 200, 2.47e10, Vector4(0, 0, 1, 1));
	_buoyancy = new BuoyancyForceGenerator(_water, 90, 999.0f, 1000);
	_buoyancy->register_rb_system(this);
	_waterTr = new physx::PxTransform(_water->position());
	RenderItem* ri = new RenderItem(CreateShape(physx::PxSphereGeometry(250)), _waterTr, Vector4(0, 0, 1, 1));
#pragma endregion

#pragma region Laimargia
	create_planet(10000, 9000, 25, 3e10, Vector4(1.0f, 0.4f, 0.7f, 1.0f));
#pragma endregion

#pragma region Collar de Andy
	_asteroidBelt = new AsteroidBeltSystem(Vector3(0, 0, 0), Vector3(1, 0, 1), 15000, 20000, _physics, _scene);
	_asteroidBelt->generate();
#pragma endregion

#pragma region Viento
	_windPlanet = create_planet(22000, 21500, 400, 2e12, Vector4(1, 1, 1, 1));
	_windPs = new AliExpressParticleSystem(_tr->p, 10);

	physx::PxVec3 tangentialVelocity = Vector3(100, 0, 0).cross(physx::PxVec3(0, 1, 0));
	Vector3 pos = Vector3(_windPlanet->geometry().sphere().radius + 100, 0, 0);
	Vector3 vel = pos.cross(tangentialVelocity) / pos.magnitudeSquared();

	_wind = new Wind(_windPlanet, vel, 0.00287, 2, _windPlanet->geometry().sphere().radius, _windPlanet->geometry().sphere().radius + 100);
	_wind->register_rb_system(this);
#pragma endregion

	set_gravities();
}

