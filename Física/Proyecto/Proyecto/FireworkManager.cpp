#include "FireworkManager.h"
#include "json.hpp"

FireworkManager::FireworkManager(MainCharacter* ch, Vector3 pos): Manager(ch), autoWork_(false), pos(pos)
{
	initFireworkRules();
}

FireworkManager::~FireworkManager()
{
}

void FireworkManager::initFireworkRules()
{
	string name = "../JSONs/Firework_Rules.json";
	std::ifstream i(name);
	
	if (i.is_open()) {                                    // Para que no intente abrir archivos que no existen
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
		rule.setParameters(0, 2, 5, Vector3(-500, 2500, -500), Vector3(500, 2800, 500), 0.1, 5, 10);
		rule.payloads.push_back(FireworkRule::Payload(1, 15));
		rule.payloads.push_back(FireworkRule::Payload(1, 8));
		rules.insert({ 0, rule });

		rule = FireworkRule();
		rule.setParameters(1, 3, 7, Vector3(-400, 1500, -400), Vector3(400, 1800, 400), 0.1, 5, 8);
		rule.payloads.push_back(FireworkRule::Payload(2, 20));
		rule.payloads.push_back(FireworkRule::Payload(2, 8));
		rules.insert({ 1, rule });

		rule = FireworkRule();
		rule.setParameters(2, 2, 5, Vector3(-100, 1000, -100), Vector3(100, 1800, 100), 0.1, 4, 7);
		rules.insert({ 2, rule });

	}

	//si luego quiero incluir el tipo '7', la rule la seteo con el tipo 7 y la inserto con el id 7
}

void FireworkManager::create(unsigned type, unsigned count, FireworkRule * rule, Firework * parent)
{
	for (int i = 0; i < count; i++) {
		rule->create(AllocNewFirework(), pos, type, parent);
	}
}

void FireworkManager::Input_FireworkCreate(unsigned type, const Firework * parent)
{
	if (fireworks.size() < MAX_FIREWORKS && !autoWork_) {
		FireworkRule* rule = GetRuleFromType(type);
		if (rule != nullptr) { Firework* newFirework = AllocNewFirework(); rule->create(newFirework, pos, type, parent); }
	}
}

FireworkManager::FireworkRule* FireworkManager::GetRuleFromType(unsigned t)
{
	map<unsigned, FireworkRule>::iterator it = rules.find(t);              //al ser un map, la busqueda es mucho mas eficiente que buscar por un vector

	if (it == rules.end())                                                //si no se encuentra ningun elemento se devuelve nullptr
		return nullptr;

	return &(*it).second;
}

Firework* FireworkManager::AllocNewFirework()
{
	Firework* f = pool.getObject();
	register_particle_in_generators(f);
	fireworks_to_introduce.push(f);                                       //LOS INTRODUCE A LA COLA PARA PUSHEARLOS DESPUES
	return f;
}

float FireworkManager::RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;

}

void FireworkManager::pushFireworks()        //Vacia la cola. Es necesario para que al crear nuevos fireworks no den errores los iteradores (puede haber otra manera...?)
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
			if (rule != nullptr) { Firework* newFirework = AllocNewFirework(); rule->create(newFirework, pos, 0, NULL); }
		}
	}
}

void FireworkManager::update(float t)
{
	if (checkDistanceBtwChar(pos.z + DIST_TO_CHECK_)) {
		pos.z -= DIST_BTW_CHAR;
	}

	autoCreateFireworks(t);
	for (vector<Firework*>::iterator it = fireworks.begin(); it != fireworks.end();)
	{
		Firework* firework = (*it);
		firework->Particle::update(t);
		if (firework->getLifeTime() > firework->getAge())
		{
			remove_particle_from_generators(firework);
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
	pushFireworks();                           //si se han creado fireworks --> se pushean
}

void FireworkManager::handle_event(unsigned char key)
{
	switch (toupper(key)) 
	{
	case 'F':
		Input_FireworkCreate();
		break;
	case ' ':
		//switch_activate();
		break;
	default:
		break;
	}
}

void FireworkManager::switch_activate()
{
	autoWork_ = !autoWork_;
}
