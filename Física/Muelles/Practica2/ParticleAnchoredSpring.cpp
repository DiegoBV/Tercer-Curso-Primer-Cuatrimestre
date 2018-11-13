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

void ParticleAnchoredSpring::deactivateWind(float t)
{
	if (w->isActive()) {
		current_time += t;
		if (current_time > TIME) {
			w->setActive(false);
			current_time = 0;
		}
	}
}

void ParticleAnchoredSpring::updateForce(Particle * particle, float t)
{
	calculateForce(particle);
	deactivateWind(t);
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
	{
		w->setActive(true);
		break;
	}
	default:
		break;
	}
}
