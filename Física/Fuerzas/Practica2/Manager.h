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
	virtual void addGenerator(ParticleForceGenerator* gen) { generators.push_back(gen); }
	//registra una particula en todos sus generadores
	virtual void register_particle_in_generators(Particula* p) { for (ParticleForceGenerator* gen : generators) { Particula::registry_.add(p, gen); } };
	//elimina una particula de la lista
	virtual void remove_particle_from_generators(Particula* p) { for (ParticleForceGenerator* gen : generators) { Particula::registry_.remove(p, gen); } };
};

