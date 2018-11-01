#pragma once
#include "ParticleForceGenerator.h"

class ParticleDrag: public ParticleForceGenerator
{
private:
	float k1;                       // Coefficient for velocity
	
	float k2;                      // Coefficient for squared velocity

	Vector3 center;               //sphere center

	physx::PxTransform transform;

	float rad;                   //sphere radius

	RenderItem* rn = nullptr;

	bool is_inside(Particula* particle);

public:
	ParticleDrag() {};

	virtual ~ParticleDrag() { delete rn; };

	ParticleDrag(float _k1, float _k2, Vector3 center = { 0, 0, 0 }, float rad = 50) : k1(_k1), k2(_k2), center(center), rad(rad), transform(center), rn(new RenderItem()) 
	{ rn->shape = CreateShape(physx::PxSphereGeometry(rad)); rn->transform = &transform; rn->color = { 1, 0, 0, 0 }; RegisterRenderItem(rn); };

	virtual void updateForce(Particula* particle, float t);
};

