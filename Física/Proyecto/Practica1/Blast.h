#pragma once
#include "ParticleForceGenerator.h"
#include "ParticleForceRegistry.h"
class Blast :
	public ParticleForceGenerator
{
private:

	float force = 100;

	Vector3 center;                                     //sphere center

	physx::PxTransform transform;

	float rad;                                        //sphere radius

	RenderItem* rn = nullptr;                        //renderItem

	bool is_inside(Vector3 pos);             //comprueba si una particula esta dentro de la esfera

	bool is_near(Vector3 pos);              //comprueba si una particula esta cerca del centro

	bool is_medium_distance(Vector3 pos);  //comprueba si una particula esta a media distancia del centro de la esfera

	void deactivate();                           //si ha comprobado todas las particulas referenciadas, desaparece

	int auxRef = 0;                              //auxiliar para comprobar si ya ha comprobado todas las particulas

	virtual void debug() { isDebugging() ? RegisterRenderItem(rn) : DeregisterRenderItem(rn); };    //debug

public:
	Blast();

	virtual ~Blast();

	Blast(float _force, float rad = 50, Vector3 center = { -10000, 30, 0 }) : force(_force), center(center), rad(rad), transform(center), rn(new RenderItem()) {
		rn->shape = CreateShape(physx::PxSphereGeometry(rad)); rn->transform = &transform; rn->color = { 1, 0, 0, 0 }; active_ = false; }
	
	virtual void updateForce(Particle* particle, float t);

	virtual void updateForce(physx::PxRigidBody* rb, float t);

	void setActive() { active_ = true; };

	void setCenter(Vector3 pos) { center = pos; transform.p = center; };


	virtual void handle_event(unsigned char key);
};

