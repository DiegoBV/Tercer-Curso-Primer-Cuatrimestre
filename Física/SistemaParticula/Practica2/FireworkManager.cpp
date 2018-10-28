#include "FireworkManager.h"
#include "json.hpp"

FireworkManager::FireworkManager(): autoWork_(false)
{
	initFireworkRules();
}

FireworkManager::~FireworkManager()
{
}

void FireworkManager::initFireworkRules()
{
	string name = ".\\JSONs\\Firework_Rules.json";
	std::ifstream i(name);
	
	if (i.is_open()) { // Para que no intente abrir archivos que no existen
		json j;
		i >> j;
		int n;
		for (int i = 0; i < j["Rules"].size(); i++) {
			FireworkRule rule;
			rule.setParameters(j["Rules"][i]["type"], j["Rules"][i]["MinAge"], j["Rules"][i]["MaxAge"], 
				Vector3(j["Rules"][i]["MinVel"][0], j["Rules"][i]["MinVel"][1], j["Rules"][i]["MinVel"][2]), 
					Vector3(j["Rules"][i]["MaxVel"][0], j["Rules"][i]["MaxVel"][1], j["Rules"][i]["MaxVel"][2]), j["Rules"][i]["Dumping"], j["Rules"][i]["MinTam"], j["Rules"][i]["MaxTam"]);

			for (int k = 0; k < j["Rules"][i]["Payloads"].size(); k++) {
				rule.payloads.push_back(FireworkRule::Payload(j["Rules"][i]["Payloads"][k]["NextType"], j["Rules"][i]["Payloads"][k]["Count"]));
			}
			rules.insert({ j["Rules"][i]["type"], rule });
		}
	}
	else {
		cout << "NO SE HA ENCONTRADO EL ARCHIVO DE LAS REGLAS DE LOS FIREWORKS, SE CREARAN REGLAS POR DEFECTO";
		FireworkRule rule;
		rule.setParameters(0, 2, 5, Vector3(-50, 250, -50), Vector3(50, 280, 50), 0.1, 4, 5);
		rule.payloads.push_back(FireworkRule::Payload(2, 15));
		rule.payloads.push_back(FireworkRule::Payload(2, 8));
		rules.insert({ 0, rule });

		rule = FireworkRule();
		rule.setParameters(2, 3, 7, Vector3(-40, 1500, -40), Vector3(40, 180, 40), 0.1, 2 , 3);
		rules.insert({ 2, rule });
	}

	//si luego quiero incluir el tipo '7', la rule la seteo con el tipo 7 y la inserto con el id 7
}

void FireworkManager::create(unsigned type, unsigned count, FireworkRule * rule, Firework * parent)
{
	for (int i = 0; i < count; i++) {
		rule->create(AllocNewFirework(), type, parent);
	}
}

void FireworkManager::Input_FireworkCreate(unsigned type, const Firework * parent)
{
	if (fireworks.size() < MAX_FIREWORKS && !autoWork_) {
		FireworkRule* rule = GetRuleFromType(type);
		if (rule != nullptr) { Firework* newFirework = AllocNewFirework(); rule->create(newFirework, type, parent); }
	}
}

FireworkManager::FireworkRule* FireworkManager::GetRuleFromType(unsigned t)
{
	map<unsigned, FireworkRule>::iterator it = rules.find(t); //al ser un map, la busqueda es mucho mas eficiente que buscar por un vector

	if (it == rules.end()) //si no se encuentra ningun elemento se devuelve nullptr
		return nullptr;

	return &(*it).second;
}

Firework* FireworkManager::AllocNewFirework()
{
	Firework* f = pool.getObject();
	fireworks_to_introduce.push(f); //LOS INTRODUCE A LA COLA PARA PUSHEARLOS DESPUES
	return f;
}

float FireworkManager::RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;

}

//Vacia la cola. Es necesario para que al crear nuevos fireworks no den errores los iteradores (puede haber otra manera...?)
void FireworkManager::pushFireworks()
{
	while (!fireworks_to_introduce.empty()) {
		fireworks.push_back(fireworks_to_introduce.front());
		fireworks_to_introduce.pop();
	}
}

void FireworkManager::autoCreateFireworks(double t)
{
	current_time += t;
	if (current_time > TIME) {
		current_time = 0;
		if (autoWork_) {
			FireworkRule* rule = GetRuleFromType(0);
			if (rule != nullptr) { Firework* newFirework = AllocNewFirework(); rule->create(newFirework, 0, NULL); }
		}
	}
}

void FireworkManager::FireworksUpdate(double t)
{
	autoCreateFireworks(t);
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
	pushFireworks(); //si se han creado fireworks --> se pushean
}

void FireworkManager::switch_activate()
{
	autoWork_ = !autoWork_;
}
