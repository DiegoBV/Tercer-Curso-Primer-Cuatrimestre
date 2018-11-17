#pragma once
#include "ParticleAbstractSpring.h"
class ParticleSpring :
	public ParticleAbstractSpring
{
private:
	// The other particle the spring is attached to
	Particle* other;

	virtual void calculateForce(Particle* particle);

public:
	ParticleSpring(Particle* _other, float _k, float _restLength) : ParticleAbstractSpring(_k, _restLength), other(_other) {
		getWind()->setWindDirection(Vector3(1, 0, 0)); getWind()->setWindForce(20); };

	virtual ~ParticleSpring() {};

	virtual void updateForce(Particle* particle, float t);
};

