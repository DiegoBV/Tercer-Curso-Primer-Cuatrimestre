#include "Blast.h"

bool Blast::is_inside(Vector3 pos)
{
	return (((center.x + rad) >= (pos.x) && (center.y + rad) >= (pos.y) && (center.z + rad) >= (pos.z)))
		&& ((center.x - rad) <= (pos.x) && (center.y - rad) <= (pos.y) && (center.z - rad) <= (pos.z));
}

bool Blast::is_near(Vector3 pos)
{
	return (((center.x + rad/2) >= (pos.x) && (center.y + rad/2) >= (pos.y) && (center.z + rad/2) >= (pos.z)))
		&& ((center.x - rad/2) <= (pos.x) && (center.y - rad/2) <= (pos.y) && (center.z - rad/2) <= (pos.z));
}

bool Blast::is_medium_distance(Vector3 pos)
{
	return (((center.x + rad / 4) >= (pos.x) && (center.y + rad / 4) >= (pos.y) && (center.z + rad / 4) >= (pos.z)))
		&& ((center.x - rad / 4) <= (pos.x) && (center.y - rad / 4) <= (pos.y) && (center.z - rad / 4) <= (pos.z));
}

void Blast::deactivate()
{
	if (auxRef >= references_) {                  //si ya ha comprobado todas las Particles que tiene referenciadas, la explosion se desactiva
		active_ = false;
		auxRef = 0;
	}
}

Blast::Blast()
{
}


Blast::~Blast()
{
	delete rn;
}

void Blast::updateForce(Particle * particle, float t)
{
	if (is_inside(particle->getPosition())) {
		Vector3 dir = particle->getPosition() - center;
		dir.normalize();

		if (is_near(particle->getPosition())) {
			particle->addForce(dir *force * 5 * particle->getMass());
		}
		else if (is_medium_distance(particle->getPosition())) {
			particle->addForce(dir *force * particle->getMass());
		}
		else {
			particle->addForce(dir *force / 5 * particle->getMass());
		}
	}

	auxRef++;

	deactivate();
}

void Blast::updateForce(physx::PxRigidBody * rb, float t)
{
	if (is_inside(rb->getGlobalPose().p)) {
		Vector3 dir = rb->getGlobalPose().p - center;
		dir.normalize();

		if (is_near(rb->getGlobalPose().p)) {
			rb->addForce(dir *force * 5 * rb->getMass());
		}
		else if (is_medium_distance(rb->getGlobalPose().p)) {
			rb->addForce(dir *force * rb->getMass());
		}
		else {
			rb->addForce(dir *force / 5 * rb->getMass());
		}
	}

	auxRef++;

	deactivate();
}

void Blast::handle_event(unsigned char key)
{
}
