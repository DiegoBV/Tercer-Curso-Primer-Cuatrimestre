#pragma once
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
protected:
	// Storage for generator-particle entry
	struct ParticleForceRegistration
	{
		Particula* particle;
		ParticleForceGenerator* fg;

		ParticleForceRegistration() : particle(nullptr), fg(nullptr) {};
		ParticleForceRegistration(Particula* particle, ParticleForceGenerator* fg) : particle(particle), fg(fg) {};
		inline bool operator==(const ParticleForceRegistration& e1) { return (e1.particle == this->particle) && (e1.fg == this->fg); };
	};

	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;
public:
	ParticleForceRegistry() {};
	// Associate generator with a particle
	void add(Particula* particle, ParticleForceGenerator* fg);
	// Remove association
	void remove(Particula* particle, ParticleForceGenerator* fg);
	// Removes all associations. Particle and Generators won't be deleted
	void clear();
	// Update all the generators in the registry
	void updateForces(float t);
};

