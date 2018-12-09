#include "Wind.h"

bool Wind::is_inside(Vector3 pos)
{
	return (((center.x + rad) >= (pos.x) && (center.y + rad) >= (pos.y) && (center.z + rad) >= (pos.z)))
		&& ((center.x - rad) <= (pos.x) && (center.y - rad) <= (pos.y) && (center.z - rad) <= (pos.z));
}

void Wind::setActive(const bool a)
{
	ParticleForceGenerator::setActive(a);
}

void Wind::updateForce(Particle * particle, float t)
{
	if (this->isActive()) {
		if (particle->getMass() <= 0.0f) return;

		if (is_inside(particle->getPosition())) {
			particle->addForce(wind_direction_ * wind_force_ * particle->getMass());
		}
	}
}

void Wind::updateForce(physx::PxRigidBody* rb, float t)
{
	if (this->isActive()) {
		if (rb->getMass() <= 0.0f) return;

		if (is_inside(rb->getGlobalPose().p)) {
			rb->addForce(wind_direction_ * wind_force_ * rb->getMass());
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
	case 'M':
		active_ = !active_;
		break;
	default:
		break;
	}
}
