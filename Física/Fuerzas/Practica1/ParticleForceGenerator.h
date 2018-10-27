#pragma once
#include "Particula.h"
class ParticleForceGenerator
{
public:
	ParticleForceGenerator() {};
	virtual ~ParticleForceGenerator() {};
	// Overload to provide functionality
	virtual void updateForce(Particula* particle, float t) = 0;
};

