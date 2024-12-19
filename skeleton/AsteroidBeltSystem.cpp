#include "AsteroidBeltSystem.h"

#include "Gravity.h"

AsteroidBeltSystem::AsteroidBeltSystem(const Vector3& center, const Vector3& plane, float min, float max, physx::PxPhysics* p, physx::PxScene* s) :
	RigidBodySystem(center, p, s),
	_plane(plane),
	_min(min),
	_max(max)
{
}

AsteroidBeltSystem::~AsteroidBeltSystem()
= default;

void AsteroidBeltSystem::update(double t)
{
}

void AsteroidBeltSystem::generate()
{
	for (int i = 0; i < 1000; ++i)
	{
		std::uniform_real_distribution<float> r(_min, _max);
		std::uniform_real_distribution<float> theta(0.0f, physx::PxTwoPi);

		float rad = r(_gen);
		float angle = theta(_gen);

		float x = rad * cos(angle);
		float z = rad * sin(angle);

		Vector3 pos = { x, 0, z };

		std::uniform_int_distribution<int> a(0, 2);
		const int rnd = a(_gen);

		physx::PxMaterial* mat = _physics->createMaterial(0.5, 0.5, 0.0);
		std::uniform_real_distribution<double> m(100, 10000);
		std::uniform_real_distribution<double> rd(50, 100);
		std::uniform_real_distribution<double> l(1, 100);
		double mass = m(_gen);
		double d;
		double radius;
		double length;
		DynamicRigidBody* rb = nullptr;
		switch (rnd)
		{
		case 0:
			radius = rd(_gen);
			d = mass /
				((4.0 / 3.0) * physx::PxPi * std::pow(radius, 3));
			rb = new DynamicRigidBody(_scene, _physics, pos, physx::PxSphereGeometry(radius), mat, {0.2f, 0.2f, 0.2f, 1.0}, d, mass);
			_dynamics.push_back(rb);
			break;
		case 1:
			length = l(_gen);
			d = mass / std::pow(length, 3);
			rb = new DynamicRigidBody(_scene, _physics, pos, physx::PxBoxGeometry(length, length, length), mat, { 0.2f, 0.2f, 0.2f, 1.0 }, d, mass);
			_dynamics.push_back(rb);
			break;
		case 2:
			radius = rd(_gen);
			length = l(_gen);
			d = mass / 
				(physx::PxPi * std::pow(radius, 2) * length) + (4.0f / 3.0f * physx::PxPi * std::pow(radius, 3));
			rb = new DynamicRigidBody(_scene, _physics, pos, physx::PxCapsuleGeometry(radius, length / 2.0f), mat, { 0.2f, 0.2f, 0.2f, 1.0 }, d, mass);
			_dynamics.push_back(rb);
		default:
			break;
		}

		double orbitalSpeed = sqrt((G * 4e15) / pos.magnitude());

		physx::PxVec3 tangentialVelocity = pos.getNormalized().cross(Vector3(0, 1, 0));
		tangentialVelocity.normalize();
		tangentialVelocity *= orbitalSpeed;
		rb->set_linear_velocity(-tangentialVelocity);
	}
}

