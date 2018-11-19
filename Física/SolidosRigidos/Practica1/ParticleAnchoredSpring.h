#pragma once
#include "ParticleAbstractSpring.h"
class ParticleAnchoredSpring :
	public ParticleAbstractSpring
{
private:

	Vector3* anchor;

	RenderItem* rn = nullptr;

	physx::PxTransform transform;

	virtual Vector3 calculateForce(Vector3 pos);
public:
	virtual ~ParticleAnchoredSpring() { delete rn; };

	ParticleAnchoredSpring(Vector3* anch, float _k, float _rest_length) : ParticleAbstractSpring(_k, _rest_length), anchor(anch), transform(*anch), rn(new RenderItem()) { rn->shape =
		CreateShape(physx::PxBoxGeometry(3, 3, 3)); rn->transform = &transform; rn->color = { 0, 1, 0, 1 }; RegisterRenderItem(rn); getWind()->setCenter(*anchor); };

	virtual void updateForce(Particle* particle, float t);

	virtual void updateForce(physx::PxRigidBody* rb, float t);
};

