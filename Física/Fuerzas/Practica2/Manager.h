#pragma once
#include "TemplatePool.h"
#include "ParticleForceGenerator.h"

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
};

