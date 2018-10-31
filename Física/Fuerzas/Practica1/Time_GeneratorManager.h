#pragma once
#include "Manager.h"
#include "Particula.h"
#include "ParticleGravity.h"
#include "ParticleForceRegistry.h"
#include <time.h>

class Time_GeneratorManager: public Manager
{
	//------------------------------------------------GENERADORES DE FUERZAS------------------------------------------------
	ParticleGravity* gravity_generator_ = nullptr;

	//------------------------------------------------PARTICLE STORAGE------------------------------------------------
	TemplatePool<Particula>* pool = nullptr;
	vector<Particula*> particles;

	//------------------------------------------------PARAMETERS------------------------------------------------
	Particula::Shape shape_;
	float time_inter = 0;
	float next_period = 0;
	float tiempo_transcurrido = 0;
	Vector3 pos;
	const int VEL_MAX_ = 50;
	const int VEL_MIN_ = 20;
	const float G_ = -75;
	const float MAX_LIFE_TIME = 3;

	//------------------------------------------------AUX METHODS------------------------------------------------
	Vector3 generateRandomVel();
	Vector3 generateRandomColor();
	void generateNewParticle(double t);
	bool checkLifeTime(vector<Particula*>::iterator& it);

public:
	virtual ~Time_GeneratorManager();

	Time_GeneratorManager(Particula::Shape shp, float t, TemplatePool<Particula>* pool, ParticleGravity* g_grav = nullptr, Vector3 pos = { 10, 30, 0 }):
			Manager(), shape_(shp), time_inter(t), pool(pool), gravity_generator_(g_grav), pos(pos) { srand(time(NULL)); };

	Time_GeneratorManager() {};

	virtual void update(double t);

	virtual void handle_event(unsigned char key);
};

