#include "ParticleSpring.h"

void ParticleSpring::calculateForce(Particle * particle)
{
	// Calculate distance vector
	Vector3 f = particle->getPosition();
	f -= other->getPosition();
	// Length
	float length = f.normalize();
	// Resulting force
	f *= -(length * getK());
	particle->addForce(f);
}

void ParticleSpring::updateForce(Particle * particle, float t)
{
	calculateForce(particle);
	getWind()->setCenter(particle->getPosition());
	deactivateWind(t);
}
