#pragma once
#include "Particula.h"
#include "Manager.h"
#include "ParticleForceRegistry.h"

class Shot_Manager: public Manager
{
private:
	//------------------------------------------------ Constantes del disparo ---------------------------------------------------
	const unsigned int DEF_DIST_TRAV = 2000;
	const Particula::Shape DEF_SHAPE = Particula::Sphere;
	const unsigned int DEF_SIZE = { 10 };
	const Vector4 DEF_COLOR = { 100, 0, 100, 1 };
	const unsigned int DEF_VEL = 100;
	const unsigned int DEF_ACC = 30;

	//------------------------------------------------PARTICLE STORAGE------------------------------------------------
	std::vector<Particula*> particles; 
	TemplatePool<Particula>* pool = nullptr;

public:
	Shot_Manager() {};

	~Shot_Manager() {};

	Shot_Manager(TemplatePool<Particula>* pool) : Manager(), pool(pool) {};

	bool checkBullet(vector<Particula*>::iterator& it);

	virtual void update(double t);

	virtual void handle_event(unsigned char key);

	void shoot();
};

