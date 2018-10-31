#include "Time_GeneratorManager.h"

Vector3 Time_GeneratorManager::generateRandomVel()
{
	Vector3 nVel = { (float)(rand() % (VEL_MAX_) - VEL_MAX_ /2), (float)(VEL_MIN_ + rand() % (VEL_MAX_ - VEL_MIN_)), (float)(rand() % (VEL_MAX_) - VEL_MAX_ /2) }; //esto es para que salgan tipo fuente y se observe la gravedad bien
	return nVel;
}

Vector3 Time_GeneratorManager::generateRandomColor()
{
	Vector3 nCol = { (float)(rand() % (11))/10, (float)(rand() % (11))/10 , (float)(rand() % (11))/10 };
	return nCol;
}

void Time_GeneratorManager::generateNewParticle(double t)
{
	tiempo_transcurrido += t;
	if (tiempo_transcurrido > next_period) {
		Particula* p = pool->generateObject(pos, generateRandomVel(), { 0, 0, 0 }, generateRandomColor());

		if (gravity_generator_ != nullptr) { Particula::registry_.add(p, gravity_generator_); }                   //la a�adimos al generador de gravedad

		p->setShape(shape_, {1});
		next_period = tiempo_transcurrido + time_inter;
		particles.push_back(p);
	}
}

bool Time_GeneratorManager::checkLifeTime(vector<Particula*>::iterator& it)
{
	if ((*it)->getLifeTime() > MAX_LIFE_TIME) {
		(*it)->setInactive();

		if (gravity_generator_ != nullptr) { Particula::registry_.remove((*it), gravity_generator_); }            //la borramos del generador de gravedad

		it = particles.erase(it);

		return true;
	}

	return false;
}

Time_GeneratorManager::~Time_GeneratorManager()
{
}

void Time_GeneratorManager::update(double t)
{
	generateNewParticle(t);
	for (vector<Particula*>::iterator it = particles.begin(); it != particles.end();) {
		(*it)->update(t);
		if (!checkLifeTime(it)) { it++; };
	}
}

void Time_GeneratorManager::handle_event(unsigned char key)
{
	//do something
}
