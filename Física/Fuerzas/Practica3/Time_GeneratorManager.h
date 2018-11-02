#pragma once
#include "Manager.h"
#include "Particle.h"
#include <time.h>

class Time_GeneratorManager: public Manager
{
	//------------------------------------------------PARTICLE STORAGE------------------------------------------------
	TemplatePool<Particle>* pool = nullptr;
	vector<Particle*> particles;

	//------------------------------------------------PARAMETERS------------------------------------------------
	Particle::Shape shape_;
	float time_inter = 0;
	float next_period = 0;
	float tiempo_transcurrido = 0;
	Vector3 pos;
	const int VEL_MAX_;
	const int VEL_MIN_;
	const float MAX_LIFE_TIME_;
	bool on = true;

	//------------------------------------------------AUX METHODS------------------------------------------------
	Vector3 generateRandomVel();
	Vector4 generateRandomColor();
	void generateNewParticle(double t);
	bool checkLifeTime(vector<Particle*>::iterator& it);


public:
	virtual ~Time_GeneratorManager();

	Time_GeneratorManager(Particle::Shape shp, float t, TemplatePool<Particle>* pool, int velMax = 50, int velMin = 20, float maxLife = 3, Vector3 pos = { 10, 30, 0 }):
			Manager(), shape_(shp), time_inter(t), pool(pool), VEL_MAX_(velMax), VEL_MIN_(velMin), MAX_LIFE_TIME_(maxLife),pos(pos) { srand(time(NULL)); };

	Time_GeneratorManager(): VEL_MAX_(0), VEL_MIN_(0), MAX_LIFE_TIME_(0) {};

	virtual void update(double t);

	virtual void handle_event(unsigned char key);
};

