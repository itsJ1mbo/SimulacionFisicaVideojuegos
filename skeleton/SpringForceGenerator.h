#pragma once
#include "ForceGenerator.h"
#include "Particle.h"

class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double l, Particle* other);

	virtual ~SpringForceGenerator() override = default;

	void update_force(Particle* particle) const;

	inline void set_k(const double k) { _k = k; }

	virtual void apply_force(double t) const override;

protected:
	double _k;
	double _length;
	Particle* _other;
};

