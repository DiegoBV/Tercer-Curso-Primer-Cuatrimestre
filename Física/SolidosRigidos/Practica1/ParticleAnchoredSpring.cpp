#include "ParticleAnchoredSpring.h"

Vector3 ParticleAnchoredSpring::calculateForce(Vector3 pos)
{
	Vector3 f = pos;
	f -= *anchor;
	// Length
	float length = f.normalize();
	// Resulting force
	f *= -((length)* getK());

	return f;
}

void ParticleAnchoredSpring::updateForce(Particle * particle, float t)
{
	particle->addForce(calculateForce(particle->getPosition()));
	deactivateWind(t);
}

void ParticleAnchoredSpring::updateForce(physx::PxRigidBody* rb, float t)
{
	rb->addForce(calculateForce(rb->getGlobalPose().p));
	deactivateWind(t);
}


