#include "ParticleForceRegistry.h"

void ParticleForceRegistry::add(Particula * particle, ParticleForceGenerator * fg)
{
	ParticleForceRegistration pFG;
	pFG.particle = particle;
	pFG.fg = fg;

	registrations.push_back(pFG); //add the new registration
}

void ParticleForceRegistry::remove(Particula * particle, ParticleForceGenerator * fg)
{
	auto it = std::find(registrations.begin(), registrations.end(), ParticleForceRegistration(particle, fg));
	registrations.erase(it);
}

void ParticleForceRegistry::clear()
{
	registrations.clear(); //clear vector
}

void ParticleForceRegistry::updateForces(float t)
{
	for (auto it = registrations.begin(); it != registrations.end(); ++it)
	{
		it->fg->updateForce(it->particle, t);
	}
}
