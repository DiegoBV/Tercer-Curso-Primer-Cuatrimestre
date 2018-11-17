#include "Time_GeneratorManager.h"
#include"Blast.h"



void Time_GeneratorManager::generateNewElement(double t)
{
	tiempo_transcurrido += t;
	if (tiempo_transcurrido > next_period) {
		Particle* p = pool->generateObject(pos, generateRandomVel(), { 0, 0, 0 }, generateRandomColor());

		register_particle_in_generators(p);

		p->setShape(shape_, {1});
		next_period = tiempo_transcurrido + time_inter;
		particles.push_back(p);
	}
}

bool Time_GeneratorManager::checkLifeTime(vector<Particle*>::iterator& it)
{
	if ((*it)->getLifeTime() > MAX_LIFE_TIME_) {
		(*it)->setInactive();

		remove_particle_from_generators((*it));            //la borramos de los generadores

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
	if (on) {
		generateNewElement(t);
	}

	for (vector<Particle*>::iterator it = particles.begin(); it != particles.end();) {
		(*it)->update(t);
		if (!checkLifeTime(it)) { it++; };
	}
}
