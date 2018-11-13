#pragma once
#include "ParticleForceGenerator.h"
#include "Wind.h"
#include "ParticleForceRegistry.h"
class ParticleAnchoredSpring :
	public ParticleForceGenerator
{
private:
	Wind* w = nullptr;

	Vector3* anchor;

	RenderItem* rn = nullptr;

	physx::PxTransform transform;

	float current_time = 0;

	const float TIME = 3;

	// Elasticity constant
	float k;

	float rest_length;

	void calculateForce(Particle* particle);

	void deactivateWind(float t);

public:
	virtual ~ParticleAnchoredSpring() { delete rn; delete w; };

	ParticleAnchoredSpring(Vector3* anch, float _k, float _rest_length) : anchor(anch), transform(*anch), k(_k), rest_length(_rest_length), rn(new RenderItem()), w(new Wind(100, { 0, 0, -1 }, { 0, 10, 0 })) { rn->shape =
		CreateShape(physx::PxBoxGeometry(3, 3, 3)); rn->transform = &transform; rn->color = { 0, 1, 0, 1 }; RegisterRenderItem(rn); w->setActive(false); };

	virtual void updateForce(Particle* particle, float t);

	virtual void handle_event(unsigned char key);

	Wind* getWind() const { return w; };
};

