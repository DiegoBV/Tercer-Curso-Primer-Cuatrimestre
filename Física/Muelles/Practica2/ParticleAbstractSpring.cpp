#include "ParticleAbstractSpring.h"

ParticleAbstractSpring::~ParticleAbstractSpring()
{
	delete w;
}

void ParticleAbstractSpring::handle_event(unsigned char key)
{
	switch (toupper(key))
	{
	case '-':
		k -= 1;
		break;
	case '+':
		k += 1;
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

void ParticleAbstractSpring::deactivateWind(float t)
{
	if (w->isActive()) {
		current_time += t;
		if (current_time > TIME) {
			w->setActive(false);
			current_time = 0;
		}
	}
}
