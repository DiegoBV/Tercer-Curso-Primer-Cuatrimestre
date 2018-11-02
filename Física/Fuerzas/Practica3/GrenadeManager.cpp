#include "GrenadeManager.h"



GrenadeManager::GrenadeManager()
{
	blast = new Blast(2000, 40);
	g = new Grenade(2, 2, blast);
}


GrenadeManager::~GrenadeManager()
{
	delete g; g = nullptr;
	delete blast; blast = nullptr;
}

void GrenadeManager::update(double t)
{
	g->update(t);
}

void GrenadeManager::handle_event(unsigned char key)
{
	switch (toupper(key))
	{
	case 'G':
		shoot();
		break;
	default:
		break;
	}
}

void GrenadeManager::shoot()
{
	if (!g->isActive()) {
		register_particle_in_generators(g);

		g->setPosition((GetCamera()->getEye()));

		g->setVelocity({GetCamera()->getDir().x * 25, abs(GetCamera()->getDir().y * 40), GetCamera()->getDir().z * 25 });        //sets de velocidad y aceleracion

		g->setActive();
	}
}
