#include "Wind.h"
#include "Particle.h"

Wind::Wind(const physx::PxVec3& vel, double k1, double k2, const physx::PxVec3& min, const physx::PxVec3& max) :
	_windVel(vel), _minZone(min), _maxZone(max), _k1(k1), _k2(k2)
{
	
}

void Wind::apply_force()
{
	for (const auto ps : _ps)
	{
		for (const auto p : ps->particles())
		{
			if(is_under_effect(p->position())) 
			{
				physx::PxVec3 diffVel = _windVel - p->velocity();
				const double magnitude = diffVel.magnitude();
				physx::PxVec3 windForce = _k1 * diffVel + _k2 * magnitude * diffVel;

				p->apply_force(windForce);
			}
		}
	}
}

bool Wind::is_under_effect(const physx::PxVec3& pos) const {
	return pos.x >= _minZone.x && pos.x <= _maxZone.x &&
		pos.y >= _minZone.y && pos.y <= _maxZone.y &&
		pos.z >= _minZone.z && pos.z <= _maxZone.z;
}