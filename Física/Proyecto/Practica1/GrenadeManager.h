#pragma once
#include "Manager.h"
#include "Grenade.h"

class GrenadeManager :
	public Manager
{
private:
	Blast * blast = nullptr;                                         //generador de fuerzas, compartido por todas las granadas

	vector<Grenade*> grenades_;

	void check_time_to_explode(Grenade*& g);                        //comprueba si la granada ha cumplido su tiempo

	void force_explosion();                                        //para debugear y explotar las granadas antes de tiempo

public:
	GrenadeManager(MainCharacter* ch = nullptr);

	virtual ~GrenadeManager();

	virtual void update(float t);

	virtual void handle_event(unsigned char key);

	void shoot();

	Blast* getBlast() const { return blast; };
};
