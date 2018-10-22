#include "Time_Generator.h"



Vector3 Time_Generator::generateRandomVel()
{
	Vector3 nVel = { (float)(rand() % (VEL_MAX_) - VEL_MAX_ /2), (float)(VEL_MIN_ + rand() % (VEL_MAX_ - VEL_MIN_)), (float)(rand() % (VEL_MAX_) - VEL_MAX_ /2) }; //esto es para que salgan tipo fuente y se observe la gravedad bien
	return nVel;
}

Vector3 Time_Generator::generateRandomColor()
{
	Vector3 nCol = { (float)(rand() % (11))/10, (float)(rand() % (11))/10 , (float)(rand() % (11))/10 };
	return nCol;
}

void Time_Generator::generateNewParticle(float time)
{
	tiempo_transcurrido += time;
	if (tiempo_transcurrido > next_period) {
		Particula* p = pool->generateObject(pos, generateRandomVel(), { 0, G_, 0 }, generateRandomColor());
		p->setShape(shape_, {1});
		next_period = tiempo_transcurrido + time_inter;
		particles.push_back(p);
	}
}

bool Time_Generator::checkLifeTime(vector<Particula*>::iterator& it)
{
	if ((*it)->lifeTime() > MAX_LIFE_TIME) {
		(*it)->setInactive();
		it = particles.erase(it);
		return true;
	}
	return false;
}

Time_Generator::~Time_Generator()
{
}

void Time_Generator::update(float time)
{
	generateNewParticle(time);
	for (vector<Particula*>::iterator it = particles.begin(); it != particles.end();) {
		(*it)->update(time);
		if (!checkLifeTime(it)) { it++; };
	}
}
