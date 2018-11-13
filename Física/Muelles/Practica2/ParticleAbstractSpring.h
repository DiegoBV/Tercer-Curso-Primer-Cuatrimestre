#pragma once
#include "ParticleForceGenerator.h"
#include "Wind.h"
#include "ParticleForceRegistry.h"

class ParticleAbstractSpring :
	public ParticleForceGenerator
{
	// Elasticity constant
	float k;

	float rest_length;

	float current_time = 0;

	const float TIME = 3;

	Wind* w = nullptr;

protected:

	void deactivateWind(float t);

public:
	ParticleAbstractSpring(float _k, float _rest_length) : k(_k), rest_length(_rest_length), w(new Wind(100, { 0, 0, -1 }, { 0, 10, 0 })) { w->setActive(false); };

	virtual ~ParticleAbstractSpring();

	virtual void updateForce(Particle* particle, float t) = 0;

	virtual void handle_event(unsigned char key);

	//-------------------------------------------------------------------GETS------------------------------------------------------------

	inline Wind* getWind() { return w; };

	inline int getK() const { return k; };

	inline int getRestLength() const { return rest_length; };

	//-------------------------------------------------------------------SETS------------------------------------------------------------

	inline void setK(int nK) { k = nK; };

	inline void setRestLength(int nrt) { rest_length = nrt; };

};

