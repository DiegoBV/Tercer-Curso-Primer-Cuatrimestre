#pragma once
#include "Manager.h"
#include "ParticleAnchoredSpring.h"
#include "ParticleSpring.h"
#include "ParticleBuoyancy.h"

class SpringManager :
	public Manager
{
private:
	vector<Particle*> particles;                  //particulas anyadidas a los muelles

	vector<ParticleAbstractSpring*> springs;      //Vector especial que controla los muelles

public:
	SpringManager(MainCharacter* ch = nullptr): Manager(ch) {};

	~SpringManager() { for (ParticleForceGenerator* gen : springs) { delete gen; } for (Particle* p : particles) { delete p; } };

	void addParticle_to_AnchoredSpring(Vector3* anchor, float k, float rest_length);                                   //anyade una particula a una posicion estatica

	void addRigid_Body_to_AnchoredSpring(physx::PxRigidDynamic* obj, Vector3* anchor, float k, float rest_length);                                   //anyade un rigid body a una posicion estatica

	void addSpring_of_TwoParticles(float k, float rest_length, Vector3 posONE = { 10, 0, 10 }, Vector3 posOTHER = { 10, 10, 10 }, Particle* one = nullptr, Particle * other = nullptr);    //anyade dos particulas unidad por un muelle

	void addSpring_of_TwoRigidBodies(float k, float rest_length, physx::PxRigidDynamic* one, physx::PxRigidDynamic* other);

	void addParticle_to_Liquid(Vector3 pos, float _maxDepth, float _volume, float _waterHeight, float _liquidDensity = 1);                  //anyade una particula con efecto de flotacion

	void addRigidBody_to_Liquid(physx::PxRigidDynamic* rb, float _maxDepth, float _volume, float _waterHeight, float _liquidDensity = 1);

	virtual void update(float t);

	virtual void handle_event(unsigned char key);
};

