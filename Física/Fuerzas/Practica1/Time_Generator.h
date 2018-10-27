#pragma once
#include "TemplatePool.h"
#include "Particula.h"
#include <time.h>

class Time_Generator
{
	Particula::Shape shape_;
	float time_inter = 0;
	float next_period = 0;
	float tiempo_transcurrido = 0;
	TemplatePool<Particula>* pool = nullptr;
	vector<Particula*> particles;
	Vector3 pos;
	const int VEL_MAX_ = 50;
	const int VEL_MIN_ = 20;
	const float G_ = -75;
	const float MAX_LIFE_TIME = 3;
	Vector3 generateRandomVel();
	Vector3 generateRandomColor();
	void generateNewParticle(float time);
	bool checkLifeTime(vector<Particula*>::iterator& it);

public:
	virtual ~Time_Generator();
	Time_Generator(Particula::Shape shp, float t, TemplatePool<Particula>* pool, Vector3 pos = { 10, 30, 0 }) : shape_(shp), time_inter(t), pool(pool), pos(pos) { srand(time(NULL)); };
	Time_Generator() {};
	void update(float time);
};

