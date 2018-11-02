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

	bool is_inside(Particula* particle);

	bool is_near(Particula* particle);

	bool is_medium_distance(Particula* particle);

	void deactivate();

	int auxRef = 0;

public:
	Blast();

	virtual ~Blast();

	Blast(float _force,  Vector3 center = { 10, 30, 0 }, float rad = 50) : force(_force), center(center), rad(rad), transform(center), rn(new RenderItem()) {
		rn->shape = CreateShape(physx::PxSphereGeometry(rad)); rn->transform = &transform; rn->color = { 1, 0, 0, 0 }; active_ = false; RegisterRenderItem(rn);
	}
	
	virtual void updateForce(Particula* particle, float t);

	virtual void handle_event(unsigned char key);
};

