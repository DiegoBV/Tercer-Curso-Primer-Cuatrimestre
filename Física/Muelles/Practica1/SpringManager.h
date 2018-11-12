#pragma once
#include "Manager.h"
#include "ParticleAnchoredSpring.h"

class SpringManager :
	public Manager
{
private:
	vector<Particle*> particles;
	vector<ParticleForceGenerator*> springs;

public:
	SpringManager() {};
	~SpringManager() { for (ParticleForceGenerator* gen : springs) { delete gen; } for (Particle* p : particles) { delete p; } };
	void addParticle_to_AnchoredSpring(Vector3* anchor, float k, float rest_length);
	void addSpring_of_TwoParticles(float k, float rest_length, Particle* one = nullptr, Particle* other = nullptr);
	virtual void update(double t);
	virtual void handle_event(unsigned char key);
};

