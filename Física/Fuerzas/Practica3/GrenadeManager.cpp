#include "GrenadeManager.h"



void GrenadeManager::check_time_to_explode(Grenade*& g)
{
	if (g->is_time_to_explode()) {
		g->explode();
		remove_particle_from_generators(g);
	}
}

void GrenadeManager::force_explosion()                     //just debug
{
	int i = 0;
	bool found = false;
	while (i < grenades_.size() && !found) {
		if (grenades_[i]->isActive()) {
			found = true;
			grenades_[i]->explode();
			remove_particle_from_generators(grenades_[i]);
		}
		i++;
	}
}

GrenadeManager::GrenadeManager(): blast(new Blast(2000, 30))   //constructora
{
	for (int i = 0; i <= 5; i++) {
		grenades_.push_back(new Grenade(2, 1.5, blast));
		grenades_.back()->setColor({ 0.5, 0.1, 0.5, 1 });
	}
}


GrenadeManager::~GrenadeManager()
{
	for (Grenade* g : grenades_) { delete g; g = nullptr; }
}

void GrenadeManager::update(double t)
{
	for (Grenade* g : grenades_) {
		if (g->isActive()) {
			g->update(t);
			check_time_to_explode(g);
		}
	}
}

void GrenadeManager::handle_event(unsigned char key)
{
	switch (toupper(key))
	{
	case 'G':
		shoot();
		break;
	case 'E':
		force_explosion();                        //just debug
		break;
	default:
		break;
	}
}

void GrenadeManager::shoot()                     //busca la primera inactiva y la dispara, no he usado pool porque solo puede disparar 5, no merece la pena
{
	int i = 0;
	bool found = false;
	while (i < grenades_.size() && !found) {
		if (!grenades_[i]->isActive()) {

			register_particle_in_generators(grenades_[i]);

			grenades_[i]->setPosition((GetCamera()->getEye()));

			grenades_[i]->setVelocity({ GetCamera()->getDir().x * 30, abs(GetCamera()->getDir().y * 50), GetCamera()->getDir().z * 30 });        //sets de velocidad y aceleracion

			grenades_[i]->setAcceleration(GetCamera()->getDir());

			grenades_[i]->setActive();

			found = true;
		}
		i++;
	}
}
