#include "ParticleForceRegistry.h"

void ParticleForceRegistry::add(Particle * particle, ParticleForceGenerator * fg)
{
	ParticleForceRegistration pFG;
	pFG.particle = particle;
	pFG.fg = fg;
	fg->addReference();

	registrations.push_back(pFG);              //add the new registration
}

void ParticleForceRegistry::remove(Particle * particle, ParticleForceGenerator * fg)
{
	auto it = std::find(registrations.begin(), registrations.end(), ParticleForceRegistration(particle, fg));

	if (it != registrations.end()) {
		registrations.erase(it);
		fg->removeReference();
	}
}

void ParticleForceRegistry::clear()
{
	registrations.clear();                    //clear vector
}

void ParticleForceRegistry::updateForces(double t)
{
	for (auto it = registrations.begin(); it != registrations.end(); ++it)
	{
		if (it->fg->isActive()) {
			it->fg->updateForce(it->particle, t);
		}
	}
}

void ParticleForceRegistry::removeGenerator(ParticleForceGenerator * fg)
{
	for (auto it = registrations.begin(); it != registrations.end();) {
		(*it).fg == fg ? it = registrations.erase(it) : it++;
	}
}
