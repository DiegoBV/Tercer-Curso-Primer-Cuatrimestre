#pragma once
#include "RenderUtils.hpp"
#include "Particle.h"
class MainCharacter
{
private:

	bool dead_;

	physx::PxRigidDynamic* pj;

	RenderItem* rn = nullptr;

	physx::PxPhysics* gPhysics = nullptr;

	physx::PxScene* gScene = nullptr;

	float JUMP_FORCE = 60;

public:

	MainCharacter(physx::PxPhysics* gPhysics, physx::PxScene* gScene, Vector3 pos = {0, 0, 0}) : gPhysics(gPhysics), gScene(gScene), 
			pj(gPhysics->createRigidDynamic(physx::PxTransform(pos))), dead_(false) { physx::PxShape* s = Particle::createShape(Particle::Sphere, { 5, 5, 5 });
				pj->attachShape(*s); physx::PxRigidBodyExt::updateMassAndInertia(*pj, 1); rn = new RenderItem(s, pj, { 0, 1, 0, 1 }); gScene->addActor(*pj); };

	virtual ~MainCharacter() { if (rn != nullptr) delete rn; };

	inline physx::PxRigidDynamic* getPj() const { return pj; };

	void setColor(Vector4 col) { rn->color = col; };

	inline void setNewJumpForce(float j) { JUMP_FORCE = j; };

	inline float getJumpForce() { return JUMP_FORCE; };

	inline bool isDead() const { return dead_; };

	inline void setDead(bool d) { dead_ = d; };
};

