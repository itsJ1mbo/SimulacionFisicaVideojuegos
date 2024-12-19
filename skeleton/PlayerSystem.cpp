#include "PlayerSystem.h"

#include <iostream>

#include "RenderUtils.hpp"
#include "RocketForce.h"

PlayerSystem::PlayerSystem(const Vector3& pos, physx::PxPhysics* p, physx::PxScene* scene) :
	RigidBodySystem(pos, p, scene),
	_rocket(nullptr),
	_camVector(0, 2, 0),
	_time(0)
{
	_rocket = new RocketForce(GetCamera()->getDir(), 200);
	_rocket->register_rb_system(this);
}

PlayerSystem::~PlayerSystem()
{
	delete _rocket;
	_rocket = nullptr;
}

void PlayerSystem::update(double t)
{
	if (_dynamics.back()->g.grounded)
	{
		physx::PxVec3 direction = _dynamics.back()->position() - _dynamics.back()->g.position;

		direction.normalize();

		physx::PxVec3 rotationAxis = _camVector.cross(direction);

		if (rotationAxis.magnitude() <= 0) return;

		rotationAxis.normalize();

		float dotProduct = _camVector.getNormalized().dot(direction.getNormalized());
		float angle = acos(dotProduct);

		physx::PxQuat targetRotation(angle, rotationAxis);

		_time += t;
		physx::PxQuat rotation = Slerp(physx::PxQuat(physx::PxIdentity), targetRotation, physx::PxClamp(_time / 1.0, 0.0, 1.0));
		_camVector = rotation.rotate(_camVector);
	}

	GetCamera()->set_eye(dynamics().back()->position() + _camVector);
}

void PlayerSystem::generate()
{
	double d = 60.0 /
		((4.0 / 3.0) * physx::PxPi * std::pow(1, 3));

	physx::PxMaterial* mat = _physics->createMaterial(0.5, 0.5, 0.0);
	DynamicRigidBody* player = new DynamicRigidBody(_scene, _physics, _tr->p, physx::PxSphereGeometry(0.5f), mat, Vector4(1, 1, 1, 1), 950, 60);

	_dynamics.push_back(player);
}

void PlayerSystem::move(const int dir) const
{
	_rocket->ser_dir(GetCamera()->getDir() * dir);
	_rocket->apply_force_dynamics(0);
}
