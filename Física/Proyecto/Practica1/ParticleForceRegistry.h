#pragma once
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
protected:
	struct ParticleForceRegistration                                // Storage for generator-particle entry
	{

		Particle* particle;
		physx::PxRigidDynamic* rigid_body;

		ParticleForceGenerator* fg;

		ParticleForceRegistration() : particle(nullptr), fg(nullptr) {};

		ParticleForceRegistration(Particle* particle, ParticleForceGenerator* fg) : particle(particle), fg(fg), rigid_body(nullptr) {};

		ParticleForceRegistration(physx::PxRigidDynamic* rb, ParticleForceGenerator* fg) : particle(nullptr), fg(fg), rigid_body(rb) {};

		inline bool operator==(const ParticleForceRegistration& e1) { return (e1.particle == this->particle) && (e1.fg == this->fg); };
	};

	typedef std::vector<ParticleForceRegistration> Registry;

	Registry registrations;

public:
	ParticleForceRegistry() {};

	void add(Particle* particle, ParticleForceGenerator* fg);       // Associate generator with a particle 

	void add(physx::PxRigidDynamic* rigid_body, ParticleForceGenerator* fg);       // Associate generator with a rigidBody
	
	void remove(Particle* particle, ParticleForceGenerator* fg);    // Remove association

	void remove(physx::PxRigidDynamic* rigid_body, ParticleForceGenerator* fg);    // Remove association
	
	void clear();                                                   // Removes all associations. Particle and Generators won't be deleted
	
	void updateForces(double t);                                    // Update all the generators in the registry

	void removeGenerator(ParticleForceGenerator* fg);
};

