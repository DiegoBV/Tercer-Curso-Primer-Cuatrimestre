#pragma once
#include "System_Manager.h"
#include "Particle.h"
#include <time.h>

class Time_GeneratorManager: public System_Manager
{
private:
	//------------------------------------------------PARTICLE STORAGE------------------------------------------------
	TemplatePool<Particle>* pool = nullptr;
	vector<Particle*> particles;

	virtual void generateNewElement(double t);
	bool checkLifeTime(vector<Particle*>::iterator& it);

public:
	virtual ~Time_GeneratorManager();

	Time_GeneratorManager(Particle::Shape shp, float t, TemplatePool<Particle>* pool, int velMax = 50, int velMin = 20, float maxLife = 3, Vector3 pos = { 10, 30, 0 }):
			System_Manager(shp, t, velMax, velMin, maxLife, pos), pool(pool) { srand(time(NULL)); };

	Time_GeneratorManager(): System_Manager() {};

	virtual void update(double t);
};

