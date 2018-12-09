#include "ParticleForceRegistry.h"

void ParticleForceRegistry::add(Particle * particle, ParticleForceGenerator * fg)
{
	ParticleForceRegistration pFG(particle, fg);

	fg->addReference();

	registrations.push_back(pFG);              //add the new registration
}

void ParticleForceRegistry::add(physx::PxRigidDynamic * rigid_body, ParticleForceGenerator * fg)
{
	ParticleForceRegistration pFG(rigid_body, fg);
	
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

void ParticleForceRegistry::remove(physx::PxRigidDynamic * rigid_body, ParticleForceGenerator * fg)
{
	auto it = std::find(registrations.begin(), registrations.end(), ParticleForceRegistration(rigid_body, fg));

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
			if(it->particle != nullptr) it->fg->updateForce(it->particle, t);
			if(it->rigid_body != nullptr) it->fg->updateForce(it->rigid_body, t);
		}
	}
}

void ParticleForceRegistry::removeGenerator(ParticleForceGenerator * fg)
{
	for (auto it = registrations.begin(); it != registrations.end();) {
		(*it).fg == fg ? it = registrations.erase(it) : it++;
	}
}
