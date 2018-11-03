#include "ParticleAnchoredSpring.h"

void ParticleAnchoredSpring::calculateForce(Particle * particle)
{
	Vector3 f = particle->getPosition();
	f -= *anchor;
	// Length
	float length = f.normalize();
	// Resulting force
	f *= -((length) * k);
	particle->addForce(f);
}

void ParticleAnchoredSpring::updateForce(Particle * particle, float t)
{
	calculateForce(particle);
}

void ParticleAnchoredSpring::handle_event(unsigned char key)
{
	switch (toupper(key))
	{
	case '-':
		k -= 0.1;
		break;
	case '+':
		k += 0.1;
		break;
	case ' ':
		//campo de fuerza (?)
		break;
	default:
		break;
	}
}
