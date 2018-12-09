#pragma once
#include "ParticleAbstractSpring.h"

class ParticleBuoyancy : public ParticleAbstractSpring
{
private:
	float maxDepth;

	float volume;

	// Considering a water plane parallel to XZ
	float waterHeight;

	virtual Vector3 calculateForce(Vector3 pos);

public:

	ParticleBuoyancy(float _maxDepth, float _volume, float _waterHeight, float _liquidDensity = 1) : ParticleAbstractSpring(_liquidDensity, _waterHeight + _maxDepth), maxDepth(_maxDepth),
		volume(_volume), waterHeight(_waterHeight) {};

	virtual void updateForce(Particle* particle, float t);

	virtual void updateForce(physx::PxRigidBody* rb, float t);

	virtual void handle_event(unsigned char key);
};

