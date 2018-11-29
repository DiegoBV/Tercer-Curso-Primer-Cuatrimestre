#pragma once
#include <time.h>
#include <map>
#include <queue>
#include "Firework.h"
#include "Manager.h"

class FireworkManager: public Manager
{

private:
	const unsigned int MAX_FIREWORKS = 5;                 //numero maximo de cohetes que se pueden disparar a la vez

	const double TIME = 5;                               //cada "time" segundos se crea un firework si esa opcion esta activada

	bool autoWork_;

	double current_time = 0;

	Vector3 pos;

	std::queue<Firework*> fireworks_to_introduce;

	struct FireworkRule
	{
		struct Payload
		{
			unsigned type;
			unsigned count;
			Payload(unsigned t_, unsigned c_) : type(t_), count(c_) {};
		};

		unsigned type;

		float minAge;
		float maxAge;

		Vector3 minVel;
		Vector3 maxVel;

		float damping;

		float minTam;
		float maxTam;

		std::vector<Payload> payloads;

		void setParameters(unsigned t, float minAge_, float maxAge_, Vector3 minVel_, Vector3 maxVel_, float damp, float minTam_, float maxTam_) {
			type = t;

			minAge = minAge_;
			maxAge = maxAge_;

			minVel = minVel_;
			maxVel = maxVel_;

			damping = damp;

			minTam = minTam_;
			maxTam = maxTam_;
		};

		void create(Firework* firework, Vector3 pos, unsigned t, const Firework* parent = NULL) const
		{
			firework->setType(t);
			firework->setAge(RandomFloat(minAge, maxAge));
			Vector3 vel = {0, 0, 0};

			if (parent)
			{ // inherit velocity from parent
				firework->setPosition(parent->getPosition());
				vel += parent->getVelocity();
			}
			else
			{
				Vector3 start = pos;
				int x = rand() % 3 - 1;
				start.x = 5.0f * x;
				firework->setPosition(start);
			}
			vel += {RandomFloat(minVel.x, maxVel.x), RandomFloat(minVel.y, maxVel.y), RandomFloat(minVel.z, maxVel.z)};
			firework->setVelocity(vel);
			// Force the mass to 1
			firework->setMass(1);
			firework->setDamping(damping);
			firework->setAcceleration({RandomFloat(minVel.x, maxVel.x)/2, RandomFloat(minVel.y, maxVel.y)/2, RandomFloat(minVel.z, maxVel.z)/2});
			firework->resetLifeTime();

			switch (t)
			{
			case 0:
				firework->setBoxShape(RandomFloat(minTam, maxTam), RandomFloat(minTam, maxTam), RandomFloat(minTam, maxTam));
				break;
			case 1:
				firework->setCapsuleShape(RandomFloat(minTam, maxTam), RandomFloat(minTam, maxTam));
				break;
			case 2:
				firework->setSphereShape(RandomFloat(minTam, maxTam));
				break;
			default:
				break;
			}
		}

		FireworkRule() {};
	};

	TemplatePool<Firework> pool;                        //podria usar la misma pool que existe pero habria que hacer casteos...

	std::map<unsigned, FireworkRule> rules;
	std::vector<Firework*> fireworks;

	void initFireworkRules();

	void create(unsigned type, unsigned count, FireworkRule* rule, Firework* parent = NULL);

	FireworkRule* GetRuleFromType(unsigned t);

	Firework* AllocNewFirework();

	static float RandomFloat(float a, float b);

	void pushFireworks();

	void autoCreateFireworks(double t);

public:
	FireworkManager(Vector3 pos = {0, 0, 0});

	virtual ~FireworkManager();

	void Input_FireworkCreate(unsigned type = 0, const Firework* parent = NULL);

	virtual void update(float t);

	virtual void handle_event(unsigned char key);

	void switch_activate();
};

