#pragma once
#include "Manager.h"
#include "Grenade.h"

class GrenadeManager :
	public Manager
{
private:
	Blast * blast = nullptr;
	Grenade* g = nullptr;

public:
	GrenadeManager();

	virtual ~GrenadeManager();

	virtual void update(double t);

	virtual void handle_event(unsigned char key);

	void shoot();

	Blast* getBlast() const { return blast; };
};

