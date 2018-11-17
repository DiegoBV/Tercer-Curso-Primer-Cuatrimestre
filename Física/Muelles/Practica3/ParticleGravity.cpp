#include "ParticleGravity.h"

void ParticleGravity::updateForce(Particle * particle, float t)
{
	if (active_) {
		if (particle->getMass() <= 0.0f) return;               //tengo un lio con esto de la masa chaval
		particle->addForce(g * particle->getMass());
	}
}
