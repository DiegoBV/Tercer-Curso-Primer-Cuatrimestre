#include "Grenade.h"



void Grenade::explosion()
{
	expl->setCenter(this->getPosition());
	expl->setActive();
	this->setInactive();
}

Grenade::Grenade()
{
}


Grenade::~Grenade()
{
}

Grenade::Grenade(float rad, float time, Blast * expl) : Particle(new RenderItem()), rad(rad), time_to_explode(time), expl(expl)
{
	setSphereShape(rad);
}

void Grenade::update(float time)
{
	if (this->isActive()) {
		Particle::update(time);

		if (getLifeTime() >= time + time_to_explode) {
			explosion();
		}
	}
}
