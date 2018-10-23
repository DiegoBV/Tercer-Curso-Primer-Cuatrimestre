#include "FireworkManager.h"



FireworkManager::FireworkManager()
{
	initFireworkRules();
}


FireworkManager::~FireworkManager()
{
}

void FireworkManager::initFireworkRules()
{
	rules.push_back(FireworkRule());
	rules[0].setParameters(0, 2, 5, Vector3(-500, 2500, -500), Vector3(500, 2800, 500), 0.1, 5, 10);

	rules[0].payloads.push_back(FireworkRule::Payload(1, 15));
	rules[0].payloads.push_back(FireworkRule::Payload(1, 8));

	rules.push_back(FireworkRule());
	rules[1].setParameters(1, 3, 7, Vector3(-400, 1500, -400), Vector3(400, 1800, 400), 0.1, 5, 8);

	rules[1].payloads.push_back(FireworkRule::Payload(2, 20));
	rules[1].payloads.push_back(FireworkRule::Payload(2, 8));

	rules.push_back(FireworkRule());
	rules[2].setParameters(2, 2, 5, Vector3(-100, 1000, -100), Vector3(100, 1800, 100), 0.1, 4, 7);
}

void FireworkManager::create(unsigned type, unsigned count, FireworkRule * rule, Firework * parent)
{
	for (int i = 0; i < count; i++) {
		rule->create(AllocNewFirework(), type, parent);
	}
}

void FireworkManager::FireworkCreate(unsigned type, const Firework * parent)
{
	FireworkRule* rule = GetRuleFromType(type);
	Firework* newFirework = AllocNewFirework();
	if (rule != nullptr) rule->create(newFirework, type, parent);
}

FireworkManager::FireworkRule* FireworkManager::GetRuleFromType(unsigned t)
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

Firework* FireworkManager::AllocNewFirework()
{
	//seria hacer toda la pesca de la pool (?) o mejor no who knows
	//por ahora creo uno y ale
	Firework* f = pool.getObject();
	fireworks_to_introduce.push(f);
	return f;
}

float FireworkManager::RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;

}

void FireworkManager::pushFireworks()
{
	while (!fireworks_to_introduce.empty()) {
		fireworks.push_back(fireworks_to_introduce.front());
		fireworks_to_introduce.pop();
	}
}

void FireworkManager::FireworksUpdate(float t)
{
	for (vector<Firework*>::iterator it = fireworks.begin(); it != fireworks.end();)
	{
		Firework* firework = (*it);
		firework->Particula::update(t);
		if (firework->lifeTime() > firework->getAge())
		{
			firework->setInactive();
			it = fireworks.erase(it);
			FireworkRule* rule = GetRuleFromType(firework->getType());
			if (rule != nullptr) {
				for (auto itPlayload = rule->payloads.begin(); itPlayload != rule->payloads.end(); ++itPlayload)
				{
					FireworkRule::Payload payload = *itPlayload;
					create(payload.type, payload.count, rule, firework);
				}
			}
		}
		else {
			it++;
		}
	}
	pushFireworks();
}
