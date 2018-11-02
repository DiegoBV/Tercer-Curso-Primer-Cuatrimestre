#pragma once
#include "Particle.h"
#include "Manager.h"

class Shot_Manager: public Manager
{
private:
	//------------------------------------------------ Constantes del disparo ---------------------------------------------------
	const unsigned int DEF_DIST_TRAV = 2000;
	const Particle::Shape DEF_SHAPE = Particle::Sphere;
	const unsigned int DEF_SIZE = { 10 };
	const Vector4 DEF_COLOR = { 100, 0, 100, 1 };
	const unsigned int DEF_VEL = 100;
	const unsigned int DEF_ACC = 30;

	//------------------------------------------------PARTICLE STORAGE------------------------------------------------
	std::vector<Particle*> particles; 
	TemplatePool<Particle>* pool = nullptr;

public:
	Shot_Manager() {};

	~Shot_Manager() {};

	Shot_Manager(TemplatePool<Particle>* pool) : Manager(), pool(pool) {};

	bool checkBullet(vector<Particle*>::iterator& it);

	virtual void update(double t);

	virtual void handle_event(unsigned char key);

	void shoot();
};

