#include "Whirlwind.h"
#include  "Particle.h"

Whirlwind::Whirlwind(double k1, double k2, const physx::PxVec3& min, const physx::PxVec3& max, double K, const physx::PxVec3& pos) :
	Wind(Vector3(0, 0, 0), k1, k2, min, max), _K(K), _pos(pos)
{

}

void Whirlwind::apply_force()
{
	for (const auto ps : _ps)
	{
		for (const auto p : ps->particles())
		{
			if (is_under_effect(p->position())) 
			{
				_windVel = vel_by_distance(p->position());

				physx::PxVec3 diffVel = _windVel - p->velocity();
				const double magnitude = diffVel.magnitude();
				physx::PxVec3 windForce = _k1 * diffVel + _k2 * magnitude * diffVel;

				p->apply_force(windForce);
			}
		}
	}
}

physx::PxVec3 Whirlwind::vel_by_distance(const physx::PxVec3& pos)
{
	return _K * Vector3(-(pos.z - _pos.z), 50 - (pos.y - _pos.y), pos.x - _pos.x);
}
