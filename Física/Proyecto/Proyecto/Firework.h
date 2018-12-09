#pragma once
#include "Particle.h"

class Firework :
	public Particle
{
private:
	
	unsigned type_;                   //tipo de payload que va a generar
	 
	float age_;                       //tiempo en explotar

public:

	Firework() {};

	Firework(RenderItem* rItem, float inverse_mass = 1.0) : Particle(rItem, inverse_mass) {};

	virtual ~Firework() {};

	//---------------------------------------------------------SETTERS--------------------------------------------

	inline virtual void setType(unsigned t) { type_ = t; this->setBoxShape(10, 10, 10); this->setColor({ (float)(rand() % (11)) / 10, (float)(rand() % (11)) / 10 , (float)(rand() % (11)) / 10, 1 }); };
	inline virtual void setAge(float a) { age_ = a; };

	//---------------------------------------------------------GETTERS--------------------------------------------

	inline unsigned getType() const { return type_; };
	inline float getAge() const { return age_; };
};


