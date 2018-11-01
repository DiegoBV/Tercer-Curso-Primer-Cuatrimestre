#include "ParticleDrag.h"

void ParticleDrag::updateForce(Particula * particle, float t)
{
	Vector3 f;
	f = particle->getVelocity();

	float dragCoeff = f.normalize();                                   // Drag coeffient
	dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

	f *= -dragCoeff;                                                   // Final force
	particle->addForce(f);
}
