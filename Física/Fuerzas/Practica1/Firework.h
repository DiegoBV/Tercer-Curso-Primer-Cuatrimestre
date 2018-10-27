#pragma once
#include "Particula.h"

class Firework :
	public Particula
{
private:
	//tipo de payload que va a generar
	unsigned type_;

	//tiempo en explotar
	float age_;

public:
	Firework() {};
	Firework(RenderItem* rItem, float inverse_mass = 1.0) : Particula(rItem, inverse_mass) {};
	virtual ~Firework() {};
	inline virtual void setType(unsigned t) { type_ = t; this->setBoxShape(10, 10, 10); this->setColor({ (float)(rand() % (11)) / 10, (float)(rand() % (11)) / 10 , (float)(rand() % (11)) / 10 }); };
	inline virtual void setAge(float a) { age_ = a; };
	inline unsigned getType() const { return type_; };
	inline float getAge() const { return age_; };
};


