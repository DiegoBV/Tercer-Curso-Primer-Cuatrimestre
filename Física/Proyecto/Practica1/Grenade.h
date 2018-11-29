#pragma once
#include "Particle.h"
#include "Blast.h"

class Grenade :
	public Particle
{
private:
	float rad;                 //radio de la granada

	float time_to_explode;    //tiempo de detonacion

	Blast* expl = nullptr;   //referencia al generador de explosion

public:
	Grenade();

	virtual ~Grenade();

	Grenade(float rad, float time, Blast* expl);

	bool is_time_to_explode() { return (getLifeTime() >= time_to_explode); };    //comprueba si ya es momento de explotar

	void explode();                                                            //activa la explosion
};

