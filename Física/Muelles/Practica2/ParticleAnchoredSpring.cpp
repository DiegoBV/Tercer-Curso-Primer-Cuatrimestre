#include "ParticleAnchoredSpring.h"

void ParticleAnchoredSpring::calculateForce(Particle * particle)
{
	Vector3 f = particle->getPosition();
	f -= *anchor;
	// Length
	float length = f.normalize();
	// Resulting force
	f *= -((length) * getK());
	particle->addForce(f);
}

void ParticleAnchoredSpring::updateForce(Particle * particle, float t)
{
	calculateForce(particle);
	deactivateWind(t);
}


