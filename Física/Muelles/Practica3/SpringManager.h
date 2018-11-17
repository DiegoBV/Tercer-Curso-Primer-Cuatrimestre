#pragma once
#include "Manager.h"
#include "ParticleAnchoredSpring.h"
#include "ParticleSpring.h"
#include "ParticleBuoyancy.h"

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
	void addSpring_of_TwoParticles(float k, float rest_length, Vector3 posONE = {10, 0, 10}, Vector3 posOTHER = { 10, 10, 10 }, Particle* one = nullptr, Particle* other = nullptr);
	void addParticle_to_Liquid(Vector3 pos, float _maxDepth, float _volume, float _waterHeight, float _liquidDensity = 1);
	virtual void update(double t);
	virtual void handle_event(unsigned char key);
};

