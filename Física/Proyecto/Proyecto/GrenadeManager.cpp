#include "GrenadeManager.h"



void GrenadeManager::check_time_to_explode(Grenade*& g)
{
	if (g->is_time_to_explode()) {
		g->explode();
		remove_particle_from_generators(g);
		mciSendString("play ../Sonidos/explosion.wav", NULL, 0, NULL);
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

GrenadeManager::GrenadeManager(MainCharacter* ch): Manager(ch), blast(new Blast(20000, 150))   //constructora
{
	for (int i = 0; i <= 0; i++) {
		grenades_.push_back(new Grenade(2, 0.7, blast));
		grenades_.back()->setColor({ 1, 0, 0, 1 });
	}
}


GrenadeManager::~GrenadeManager()
{
	for (Grenade* g : grenades_) { delete g; g = nullptr; }
}

void GrenadeManager::update(float t)
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
	case '\r':
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

			grenades_[i]->setPosition(ch->getPj()->getGlobalPose().p);

			grenades_[i]->setVelocity({ 0, 70, ch->getPj()->getLinearVelocity().z*3 });        //sets de velocidad y aceleracion

			grenades_[i]->setAcceleration(GetCamera()->getDir());

			grenades_[i]->setActive();

			found = true;
		}
		i++;
	}
}
