#pragma once
#include "TemplatePool.h"
#include "ParticleForceGenerator.h"
#include "ParticleForceRegistry.h"

class Manager
{
protected:
	//------------------------------------------------GENERADORES DE FUERZAS------------------------------------------------
	vector<ParticleForceGenerator*> generators;

public:
	Manager() {};

	virtual ~Manager() {};

	virtual void update(double t) = 0;                        //virtual para poder llamarlo con vectores, update

	virtual void handle_event(unsigned char key) = 0;         //virtual para poder llamarlo con vectores, handle_event

	virtual void addGenerator(ParticleForceGenerator* gen) { generators.push_back(gen); };

	virtual void addGenerators(const vector<ParticleForceGenerator*>& gens) { for (ParticleForceGenerator* gen : gens) { generators.push_back(gen); } };

	//registra una Particle en todos sus generadores
	virtual void register_particle_in_generators(Particle* p) { for (ParticleForceGenerator* gen : generators) { if(gen != nullptr) Particle::registry_.add(p, gen); } };

	//elimina una Particle de la lista
	virtual void remove_particle_from_generators(Particle* p) { for (ParticleForceGenerator* gen : generators) { if(gen != nullptr) Particle::registry_.remove(p, gen); } };

	//registra un rigidBody en todos sus generadores
	void register_rigid_body_in_generators(physx::PxRigidDynamic* obj) { for (ParticleForceGenerator* gen : generators) { if (gen != nullptr) Particle::registry_.add(obj, gen); } };

	//elimina un rigidBody de la lista
	void remove_rigid_body_from_generators(physx::PxRigidDynamic* obj) { for (ParticleForceGenerator* gen : generators) { if (gen != nullptr) Particle::registry_.remove(obj, gen); } };
};

