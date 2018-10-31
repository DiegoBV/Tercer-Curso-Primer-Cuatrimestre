#pragma once
#include "ParticleForceGenerator.h"

class ParticleDrag: public ParticleForceGenerator
{
private:
	float k1;                       // Coefficient for velocity
	
	float k2;                      // Coefficient for squared velocity

public:
	ParticleDrag() {};
	virtual ~ParticleDrag() {};
	ParticleDrag(float _k1, float _k2) : k1(_k1), k2(_k2) {};
	virtual void updateForce(Particula* particle, float t);
};

