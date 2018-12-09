#pragma once
#include "ParticleAbstractSpring.h"
class ParticleSpring :
	public ParticleAbstractSpring
{
private:
	// The other particle the spring is attached to
	Particle* other;

	physx::PxRigidDynamic* other_r;

	virtual Vector3 calculateForce(Vector3 pos);

public:
	ParticleSpring(Particle* _other, float _k, float _restLength) : ParticleAbstractSpring(_k, _restLength), other(_other), other_r(nullptr) {
		getWind()->setWindDirection(Vector3(1, 0, 0)); getWind()->setWindForce(20); };

	ParticleSpring(physx::PxRigidDynamic * _other, float _k, float _restLength) : ParticleAbstractSpring(_k, _restLength), other_r(_other), other(nullptr) {
		getWind()->setWindDirection(Vector3(1, 0, 0)); getWind()->setWindForce(20);
	};

	virtual ~ParticleSpring() {};

	virtual void updateForce(Particle* particle, float t);

	virtual void updateForce(physx::PxRigidBody* rb, float t);
};

