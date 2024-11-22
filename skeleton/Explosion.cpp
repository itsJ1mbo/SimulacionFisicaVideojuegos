#include "Explosion.h"
#include "Particle.h"
#include <cmath>

Explosion::Explosion(double R, const physx::PxVec3& c, double K, double t) :
	_radius(R), _center(c), _K(K), _t(t)
{

}

void Explosion::apply_force(double t)
{
	for (const auto ps : _ps)
	{
		for (const auto p : ps->particles())
		{
			const Vector3 pos = p->position();
			if (r(pos) < _radius)
			{
				const Vector3 explosiveForce = (_K / pow(r(pos), 2)) * 
												Vector3(pos.x - _center.x, pos.y - _center.y, pos.z - _center.z) * 
												pow(E, -t / _t);

				p->apply_force(explosiveForce);
			}
		}
	}
}

double Explosion::r(const physx::PxVec3& pos) const
{
	return sqrt(pow(pos.x - _center.x, 2) + pow(pos.y - _center.y, 2) + pow(pos.z - _center.z, 2));
}
