#pragma once
#include <list>
#include "core.hpp"
#include "StaticRigidBody.h"
#include "DynamicRigidBody.h"

class RigidBodySystem
{
public:
	explicit RigidBodySystem(const Vector3& pos, physx::PxPhysics* p, physx::PxScene* scene) :
								_tr(new physx::PxTransform(pos)),
								_physics(p),
								_scene(scene) {}

	virtual ~RigidBodySystem()
	{
		delete _tr;
		_tr = nullptr;

		for (auto rb : _dynamics) {
			delete rb;
			rb = nullptr;
		}
		_dynamics.clear();

		for (auto rb : _statics) {
			delete rb;
			rb = nullptr;
		}
		_statics.clear();
	}

	virtual void update(double t) = 0;

	std::list<DynamicRigidBody*> dynamics() const { return _dynamics; }
	std::list<StaticRigidBody*> statics() const { return _statics; }

protected:
	std::list<DynamicRigidBody*> _dynamics;
	std::list<StaticRigidBody*> _statics;
	physx::PxTransform* _tr;
	physx::PxPhysics* _physics;
	physx::PxScene* _scene;

	virtual void generate() = 0;
};

