#pragma once
#include "Particle.h"
#include "Blast.h"

class Grenade :
	public Particle
{
private:
	float rad;
	float time_to_explode;
	Blast* expl = nullptr;
	void explosion();
public:
	Grenade();
	virtual ~Grenade();
	Grenade(float rad, float time, Blast* expl);
	virtual void update(float time);
};

