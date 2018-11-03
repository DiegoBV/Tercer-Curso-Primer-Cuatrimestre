#pragma once
#include "ParticleForceGenerator.h"
class ParticleAnchoredSpring :
	public ParticleForceGenerator
{
private:
	Vector3* anchor;

	RenderItem* rn = nullptr;

	physx::PxTransform transform;

	// Elasticity constant
	float k;

	float ext_limit;

	void calculateForce(Particle* particle);

public:
	virtual ~ParticleAnchoredSpring() { delete rn; };

	ParticleAnchoredSpring(Vector3* anch, float _k, float _extLimit) : anchor(anch), transform(*anch), k(_k), ext_limit(_extLimit), rn(new RenderItem()) { rn->shape =
		CreateShape(physx::PxBoxGeometry(3, 3, 3)); rn->transform = &transform; rn->color = { 0, 1, 0, 1 }; RegisterRenderItem(rn); };

	virtual void updateForce(Particle* particle, float t);
};

