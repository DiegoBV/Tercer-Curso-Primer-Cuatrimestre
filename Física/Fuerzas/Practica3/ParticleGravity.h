#pragma once
#include "ParticleForceGenerator.h"
class ParticleGravity :
	public ParticleForceGenerator
{
private:
	Vector3 g;                  //Acceleration for gravity

public:
	ParticleGravity() {};
	ParticleGravity(const Vector3& gravity) : g(gravity) {}
	virtual void updateForce(Particle* particle, float t);
	virtual ~ParticleGravity() {};
};

