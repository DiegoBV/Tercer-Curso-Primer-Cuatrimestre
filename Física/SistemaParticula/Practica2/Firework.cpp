#include "Firework.h"



void Firework::initFireworkRules()
{
	rules.push_back(FireworkRule());
	rules[0].setParameters(3, 0.5, 0.4, Vector3(-5, 25, -5), Vector3(5, 28, 5), 0.1);

	rules[0].payloads.push_back(FireworkRule::Payload(3, 5));
	rules[0].payloads.push_back(FireworkRule::Payload(5, 5));

	fireworks.push_back(this);
}

void Firework::FireworksCreate(unsigned type, const Firework * parent)
{
	FireworkRule* rule = GetRuleFromType(type);
	Firework* newFirework = AllocNewFirework();
	if(rule != nullptr) rule->create(newFirework, parent);
}

Firework::FireworkRule* Firework::GetRuleFromType(unsigned t) 
{
	bool found = false;
	int i = 0;
	while (i < rules.size() && !found) {
		if (rules[i].type == t) {
			found = true;
		}
		else {
			i++;
		}
	}

	if (!found) {
		return nullptr;
	}
	else {
		return &rules[i];
	}
}

Firework * Firework::AllocNewFirework()
{
	//seria hacer toda la pesca de la pool (?) o mejor no who knows
	//por ahora creo uno y ale
	Firework* f = new Firework(new RenderItem());
	f->setActive();
	fireworks.push_back(f);
	return f;
}

void Firework::FireworksUpdate(float t)
{
	for (int i = 0; i < fireworks.size(); i++)
	{
		Firework* firework = fireworks[i];
		firework->Particula::update(t);
		if (firework->isActive())
		{
			if (firework->lifeTime() > firework->age_)
			{
				FireworkRule* rule = GetRuleFromType(firework->type_);
				firework->setInactive();
				//todo va mal, no se borran del vector, no hacen lo que tienen que hacer en general, esto de las reglas es incomprensible lul
				//CREO QUE SE REFIERE A QUE HAGAMOS UN MANAGER DE FIREWORKS, QUE TENGA LAS REGLAS Y TAL---> TIENE MAS SENTIDO
				for (auto itPlayload = rule->payloads.begin(); itPlayload != rule->payloads.end(); ++itPlayload)
				{
					FireworkRule::Payload payload = *itPlayload;
					rule->create(AllocNewFirework(), firework); // ??
				}
			}
		}
	}
}

Firework::Firework()
{
	srand(time(NULL));
}


Firework::~Firework()
{
}

void Firework::update(float time)
{
	FireworksUpdate(time);
}
