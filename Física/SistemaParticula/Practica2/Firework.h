#pragma once
#include "Particula.h"
#include <time.h>

class Firework :
	public Particula
{
private:
	//tipo de payload que va a generar
	unsigned type_;

	//tiempo en explotar
	float age_;


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

		std::vector<Payload> payloads;

		void setParameters(unsigned t, float minAge_, float maxAge_, Vector3 minVel_,Vector3 maxVel_, float damp) {
			type = t;

			minAge = minAge_;
			maxAge = maxAge_;

			minVel = minVel_;
			maxVel = maxVel_;

			damping = damp;
		};

		void create(Firework* firework, const Firework* parent = NULL) const
		{
			firework->setType(type);
			//firework->setAge((float)(minAge + rand() % ((int)maxAge - (int)minAge)));
			firework->setAge(2);
			Vector3 vel;

			if (parent)
			{ // inherit velocity from parent
				firework->setPosition(parent->getPosition());
				vel += parent->v;
			}
			else
			{
				Vector3 start;
				int x = rand() % 3 - 1;
				start.x = 5.0f * x;
				firework->setPosition(start);
			}
			vel += {(float)(rand()% 20), (float)(rand()% 30), (float)(rand()% 40)};
			firework->v = vel;
			// Force the mass to 1
			firework->setMass(1);
			firework->setDamping(damping);
			firework->a = {20, -10, 30};
			firework->resetLifeTime();
		}

		FireworkRule() {};
	};

	std::vector<FireworkRule> rules;
	std::vector<Firework*> fireworks;

	void initFireworkRules();

	void FireworksCreate(unsigned type, const Firework* parent);

	FireworkRule* GetRuleFromType(unsigned t);

	Firework* AllocNewFirework();

	void FireworksUpdate(float t);
	
public:
	Firework();
	Firework(RenderItem* rItem, float inverse_mass = 1.0) : Particula(rItem, inverse_mass) { initFireworkRules(); };
	virtual ~Firework();
	virtual void update(float time);
	inline virtual void setType(unsigned t) { type_ = t; this->setBoxShape(10, 10, 10);};
	inline virtual void setAge(float a) { age_ = a; };
};


