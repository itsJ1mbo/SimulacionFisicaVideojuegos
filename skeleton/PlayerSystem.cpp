#include "PlayerSystem.h"

#include <iostream>

#include "RenderUtils.hpp"
#include "RocketForce.h"

#define M_PI 3.14159265358979323846

PlayerSystem::PlayerSystem(const Vector3& pos, physx::PxPhysics* p, physx::PxScene* scene) :
	RigidBodySystem(pos, p, scene)
{
	GetCamera()->set_eye(pos + Vector3(0, 20, 50));
	GetCamera()->set_dir(Vector3(0, 0, -1));

	_rocket = new RocketForce(GetCamera()->getDir(), 100);
	_rocket->register_rb_system(this);
}

PlayerSystem::~PlayerSystem()
{
	delete _rocket;
	_rocket = nullptr;
}

void PlayerSystem::update(double t)
{
	GetCamera()->set_eye(dynamics().back()->position() + Vector3(0, 2, 0));
	std::cout << "POS: " << _dynamics.front()->position().x << " " << _dynamics.front()->position().y << " " << _dynamics.front()->position().z << std::endl;
}

void PlayerSystem::generate()
{
	float d = 40 /
		((4 / 3) * M_PI * std::pow(1, 3));

	physx::PxMaterial* mat = _physics->createMaterial(0.5, 0.5, 0.0);
	DynamicRigidBody* player = new DynamicRigidBody(_scene, _physics, _tr->p, physx::PxSphereGeometry(1), mat, Vector4(1, 1, 1, 1), d, 40);

	_dynamics.push_back(player);
}

void PlayerSystem::move() const
{
	_rocket->ser_dir(GetCamera()->getDir());
	_rocket->apply_force_dynamics();
}
