#include "Wind.h"

bool Wind::is_inside(Particula * particle)
{
	Vector3 pos = particle->getPosition();
	return ((center.x + rad) - abs(pos.x) >= 0 && (center.y + rad) - abs(pos.y) >= 0 && (center.z + rad) - abs(pos.z) >= 0);
}

void Wind::updateForce(Particula * particle, float t)
{
	if (particle->getMass() <= 0.0f) return;

	if (is_inside(particle)) {
		particle->addForce(wind_direction_ * wind_force_ * particle->getMass());
	}
}

void Wind::handle_event(unsigned char key)
{
	switch (toupper(key))
	{
	case 'P':
		changeDirection();
		break;
	default:
		break;
	}
}
