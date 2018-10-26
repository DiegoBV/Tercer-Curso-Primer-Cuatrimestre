#pragma once
#include "Firework.h"
#include "TemplatePool.h"
#include <time.h>
#include <map>
#include <queue>

class FireworkManager
{

private:
	const unsigned int MAX_FIREWORKS = 5; //numero maximo de cohetes que se pueden disparar a la vez

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

		float GRAVITY_;

		std::vector<Payload> payloads;

		void setParameters(unsigned t, float minAge_, float maxAge_, Vector3 minVel_, Vector3 maxVel_, float damp, float minTam_, float maxTam_, float G = -25) {
			type = t;

			minAge = minAge_;
			maxAge = maxAge_;

			minVel = minVel_;
			maxVel = maxVel_;

			damping = damp;

			minTam = minTam_;
			maxTam = maxTam_;

			GRAVITY_ = G;
		};

		void create(Firework* firework, unsigned t, const Firework* parent = NULL) const
		{
			firework->setType(t);
			firework->setAge(RandomFloat(minAge, maxAge));
			Vector3 vel = {0, 0, 0};

			if (parent)
			{ // inherit velocity from parent
				firework->setPosition(parent->getPosition());
				vel += parent->v;
			}
			else
			{
				Vector3 start = {0, 0, 0};
				int x = rand() % 3 - 1;
				start.x = 5.0f * x;
				firework->setPosition(start);
			}
			vel += {RandomFloat(minVel.x, maxVel.x), RandomFloat(minVel.y, maxVel.y), RandomFloat(minVel.z, maxVel.z)};
			firework->v = vel;
			// Force the mass to 1
			firework->setMass(1);
			firework->setDamping(damping);
			firework->a = { RandomFloat(minVel.x, maxVel.x), GRAVITY_, RandomFloat(minVel.x, maxVel.x) };
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

	TemplatePool<Firework> pool; //podria usar la misma pool que existe pero habria que hacer casteos...

	std::map<unsigned, FireworkRule> rules;
	std::vector<Firework*> fireworks;

	void initFireworkRules();

	void create(unsigned type, unsigned count, FireworkRule* rule, Firework* parent = NULL);

	FireworkRule* GetRuleFromType(unsigned t);

	Firework* AllocNewFirework();

	static float RandomFloat(float a, float b);

	void pushFireworks();
public:
	FireworkManager();
	virtual ~FireworkManager();
	void FireworkCreate(unsigned type, const Firework* parent = NULL);
	void FireworksUpdate(float t);
};

