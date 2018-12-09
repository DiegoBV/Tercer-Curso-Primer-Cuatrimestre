#include "Shot_Manager.h"

bool Shot_Manager::checkBullet(vector<Particle*>::iterator & it)
{
	if ((*it)->getDistanceTraveled() > DEF_DIST_TRAV) {
		(*it)->setInactive();

		remove_particle_from_generators((*it));

		it = particles.erase(it);
		return true;
	}

	return false;
}

void Shot_Manager::update(float t)
{
	for (vector<Particle*>::iterator it = particles.begin(); it != particles.end();) {
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
	Particle* p = pool->getObject();                       //se busca una Particle inactiva en la pool (y se activa). Si no existe, se crea una nueva

	p->setShape(DEF_SHAPE, DEF_SIZE);                       //set de la forma, color, velocidad, aceleracion...

	p->setPosition((GetCamera()->getEye()));
	p->setColor(DEF_COLOR);

	p->setVelocity(GetCamera()->getDir() * DEF_VEL);        //sets de velocidad y aceleracion
	p->setAcceleration(GetCamera()->getDir() * DEF_ACC);

	register_particle_in_generators(p);

	particles.push_back(p);                                //se añade al vector de Particles para poder actualizarlas
}
