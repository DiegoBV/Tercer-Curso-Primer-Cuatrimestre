#pragma once
#include "Manager.h"
#include "ParticleAnchoredSpring.h"
#include "ParticleSpring.h"

class SpringManager :
	public Manager
{
private:
	vector<Particle*> particles;
	vector<ParticleAbstractSpring*> springs;

public:
	SpringManager() {};
	~SpringManager() { for (ParticleForceGenerator* gen : springs) { delete gen; } for (Particle* p : particles) { delete p; } };
	void addParticle_to_AnchoredSpring(Vector3* anchor, float k, float rest_length);
	void addSpring_of_TwoParticles(float k, float rest_length, Vector3 posONE = {10, 0, 10}, Vector3 posOTHER = { 10, 10, 10 }, Particle* one = nullptr, Particle* other = nullptr);
	virtual void update(double t);
	virtual void handle_event(unsigned char key);
};

