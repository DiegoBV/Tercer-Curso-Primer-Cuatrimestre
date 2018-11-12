#include "Wind.h"

bool Wind::is_inside(Particle * particle)
{
	Vector3 pos = particle->getPosition();
	return (((center.x + rad) >= (pos.x) && (center.y + rad) >= (pos.y) && (center.z + rad) >= (pos.z)))
		&& ((center.x - rad) <= (pos.x) && (center.y - rad) <= (pos.y) && (center.z - rad) <= (pos.z));
}

void Wind::setActive(const bool a)
{
	ParticleForceGenerator::setActive(a);
	if (!this->isActive()) {
		debug_ = true;
		debug();
	}
	else {
		debug_ = false;
		debug();
	}
}

void Wind::updateForce(Particle * particle, float t)
{
	if (this->isActive()) {
		if (particle->getMass() <= 0.0f) return;

		if (is_inside(particle)) {
			particle->addForce(wind_direction_ * wind_force_ * particle->getMass());
		}
	}
}

void Wind::handle_event(unsigned char key)
{
	switch (toupper(key))
	{
	case 'P':
		changeDirection();
		break;
	case 'B':
		debug();
		break;
	case 'M':
		active_ = !active_;
		break;
	default:
		break;
	}
}
