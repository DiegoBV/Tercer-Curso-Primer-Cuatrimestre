#include "ParticleSpring.h"

Vector3 ParticleSpring::calculateForce(Vector3 pos)
{
	// Calculate distance vector
	Vector3 f = pos;
	if (other != nullptr) f -= other->getPosition(); else f -= other_r->getGlobalPose().p;
	// Length
	float length = f.normalize();
	// Resulting force
	f *= -((length - getRestLength()) * getK());
	return f;
}

void ParticleSpring::updateForce(Particle * particle, float t)
{
	particle->addForce(calculateForce(particle->getPosition()));
	getWind()->setCenter(particle->getPosition());
	deactivateWind(t);
}

void ParticleSpring::updateForce(physx::PxRigidBody * rb, float t)
{
	//A VER LOKO QUE AQUI HAGO QUE SE UNAN DOS PARTICULAS, TENGO QUE METER OTRO PUNTERILLO A UN RIGID BODY PERO HOY DA MUCHA PEREZAAAAAAAAAAAAAAAAA!!!!!!!!!
	rb->addForce(calculateForce(rb->getGlobalPose().p));
	getWind()->setCenter(rb->getGlobalPose().p);
	deactivateWind(t);
}
