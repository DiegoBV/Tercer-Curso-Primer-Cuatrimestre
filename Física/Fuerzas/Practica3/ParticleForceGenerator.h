#pragma once
#include "Particula.h"
class ParticleForceGenerator
{
protected:
	int references_ = 0;
	bool active_ = true;

public:
	ParticleForceGenerator() {};

	virtual ~ParticleForceGenerator() {};

	virtual void updateForce(Particula* particle, float t) = 0;        // Overload to provide functionality
	virtual void handle_event(unsigned char key) {};
	void addReference() { references_++; };
	void removeReference() { references_--; };
	bool isActive() const { return active_; };
};

