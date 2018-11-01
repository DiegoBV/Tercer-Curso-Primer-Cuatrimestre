#include "Shot_Manager.h"

bool Shot_Manager::checkBullet(vector<Particula*>::iterator & it)
{
	if ((*it)->getDistanceTraveled() > DEF_DIST_TRAV) {
		(*it)->setInactive();

		for (ParticleForceGenerator* gen : generators) { Particula::registry_.remove((*it), gen); }

		it = particles.erase(it);
		return true;
	}

	return false;
}

void Shot_Manager::update(double t)
{
	for (vector<Particula*>::iterator it = particles.begin(); it != particles.end();) {
		(*it)->update(t);
		if (!checkBullet(it)) { it++; }                //si ninguna bala ha desaparecido se aumenta el iterador, si desaparece el iterador aumenta al borrar el contenido
	}
}

void Shot_Manager::handle_event(unsigned char key)
{
	switch (toupper(key))
	{
	case 'X':
		shoot();
		break;
	default:
		break;
	}
}

void Shot_Manager::shoot()
{
	Particula* p = pool->getObject();                       //se busca una particula inactiva en la pool (y se activa). Si no existe, se crea una nueva

	p->setShape(DEF_SHAPE, DEF_SIZE);                       //set de la forma, color, velocidad, aceleracion...

	p->setPosition((GetCamera()->getEye()));
	p->setColor(DEF_COLOR);

	p->setVelocity(GetCamera()->getDir() * DEF_VEL);        //sets de velocidad y aceleracion
	p->setAcceleration(GetCamera()->getDir() * DEF_ACC);

	for (ParticleForceGenerator* gen : generators) { Particula::registry_.add(p, gen); }

	particles.push_back(p);                                //se a�ade al vector de particulas para poder actualizarlas
}
