#pragma once
#include "Particula.h"
class ParticleForceGenerator
{
public:
	ParticleForceGenerator() {};

	virtual ~ParticleForceGenerator() {};

	virtual void updateForce(Particula* particle, float t) = 0;        // Overload to provide functionality
	virtual void handle_event(unsigned char key) {};
};

