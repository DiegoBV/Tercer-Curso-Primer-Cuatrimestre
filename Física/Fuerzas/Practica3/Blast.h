#pragma once
#include "ParticleForceGenerator.h"
#include "ParticleForceRegistry.h"
class Blast :
	public ParticleForceGenerator
{
private:

	float force = 100;

	Vector3 center;               //sphere center

	physx::PxTransform transform;

	float rad;                   //sphere radius

	RenderItem* rn = nullptr;

	bool is_inside(Particle* particle);

	bool is_near(Particle* particle);

	bool is_medium_distance(Particle* particle);

	void deactivate();

	int auxRef = 0;

public:
	Blast();

	virtual ~Blast();

	Blast(float _force, float rad = 50, Vector3 center = { -10000, 30, 0 }) : force(_force), center(center), rad(rad), transform(center), rn(new RenderItem()) {
		rn->shape = CreateShape(physx::PxSphereGeometry(rad)); rn->transform = &transform; rn->color = { 1, 0, 0, 0 }; active_ = false; RegisterRenderItem(rn); }
	
	virtual void updateForce(Particle* particle, float t);

	void setActive() { active_ = true; };

	void setCenter(Vector3 pos) { center = pos; transform.p = center; };
};

