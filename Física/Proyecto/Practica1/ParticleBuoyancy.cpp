#include "ParticleBuoyancy.h"


Vector3 ParticleBuoyancy::calculateForce(Vector3 pos)
{
	float depth = pos.y;
	if (depth > (getRestLength()))                 //restLength =  maxDepth + waterHeight
												   // Out of the water -> nothing to do
		return Vector3(0, 0, 0);

	Vector3 f(0.0f, 0.0f, 0.0f);
	if (depth <= (waterHeight - maxDepth))
	{ // Totally under the water
		f.y = getK() * volume;                     //k = liquidDensity
	}
	else
	{
		float depthExterior = getRestLength();
		float volumeFactor = (depth - depthExterior) / (2 * maxDepth);
		f.y = getK() * volumeFactor * volume;
	}

	return f;
}

void ParticleBuoyancy::updateForce(Particle* particle, float t)
{
	particle->addForce(calculateForce(particle->getPosition()));
	deactivateWind(t);
}

void ParticleBuoyancy::updateForce(physx::PxRigidBody * rb, float t)
{
	rb->addForce(calculateForce(rb->getGlobalPose().p));
	deactivateWind(t);
}

void ParticleBuoyancy::handle_event(unsigned char key)
{
	ParticleAbstractSpring::handle_event(key);

	switch (toupper(key))
	{
	case '1':
		waterHeight++;
		setRestLength(getRestLength() + 1);
		break;
	case '2':
		waterHeight--;
		setRestLength(getRestLength() - 1);
		break;
	case '3':
		maxDepth++;
		setRestLength(getRestLength() + 1);
		break;
	case '4':
		maxDepth--;
		setRestLength(getRestLength() - 1);
		break;
	case '5':
		volume++;
		break;
	case '6':
		volume--;
		break;
	default:
		break;
	}
}
