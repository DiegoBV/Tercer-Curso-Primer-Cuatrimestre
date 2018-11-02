#include "Time_GeneratorManager.h"
#include"Blast.h"

Vector3 Time_GeneratorManager::generateRandomVel()
{
	Vector3 nVel = { (float)(rand() % (VEL_MAX_) - VEL_MAX_ /2), (float)(VEL_MIN_ + rand() % (VEL_MAX_ - VEL_MIN_)), (float)(rand() % (VEL_MAX_) - VEL_MAX_ /2) }; //esto es para que salgan tipo fuente y se observe la gravedad bien
	return nVel;
}

Vector4 Time_GeneratorManager::generateRandomColor()
{
	Vector4 nCol = { (float)(rand() % (11))/10, (float)(rand() % (11))/10 , (float)(rand() % (11))/10, 1 };
	return nCol;
}

void Time_GeneratorManager::generateNewParticle(double t)
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
	if ((*it)->getLifeTime() > MAX_LIFE_TIME) {
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
		generateNewParticle(t);
	}

	for (vector<Particle*>::iterator it = particles.begin(); it != particles.end();) {
		(*it)->update(t);
		if (!checkLifeTime(it)) { it++; };
	}
}

void Time_GeneratorManager::handle_event(unsigned char key)
{
	//do something
	switch (toupper(key))
	{
	case 'T':
		on = !on;
		break;
	default:
		break;
	}
}
