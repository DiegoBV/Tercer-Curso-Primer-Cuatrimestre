#include "ParticleDrag.h"

bool ParticleDrag::is_inside(Particula * particle)
{
	Vector3 pos = particle->getPosition();
	return ((center.x + rad) - abs(pos.x) >= 0 && (center.y + rad) - abs(pos.y) >= 0 && (center.z + rad) - abs(pos.z) >= 0);
}

void ParticleDrag::updateForce(Particula * particle, float t)
{
	if (is_inside(particle)) {  //no tengo claro si esto es el viento je ---> no lo es ----> hacer una nueva clase
		Vector3 f;
		f = particle->getVelocity();

		float dragCoeff = f.normalize();                                   // Drag coeffient
		dragCoeff = k1 * dragCoeff + k2 * dragCoeff * dragCoeff;

		f *= -dragCoeff;                                                   // Final force
		particle->addForce(f);
	}
}
