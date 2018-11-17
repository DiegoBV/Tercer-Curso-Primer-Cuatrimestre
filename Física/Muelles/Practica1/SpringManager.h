#pragma once
#include "Manager.h"
#include "ParticleAnchoredSpring.h"

class SpringManager :
	public Manager
{
private:
	vector<Particle*> particles;                  //particulas anyadidas a los muelles

	vector<ParticleForceGenerator*> springs;      //Vector especial que controla los muelles

public:
	SpringManager() {};

	~SpringManager() { for (ParticleForceGenerator* gen : springs) { delete gen; } for (Particle* p : particles) { delete p; } };

	void addParticle_to_AnchoredSpring(Vector3* anchor, float k, float rest_length);                                   //anyade una particula a una posicion estatica

	void addSpring_of_TwoParticles(float k, float rest_length, Particle* one = nullptr, Particle* other = nullptr);    //anyade dos particulas unidad por un muelle

	virtual void update(double t);

	virtual void handle_event(unsigned char key);
};

