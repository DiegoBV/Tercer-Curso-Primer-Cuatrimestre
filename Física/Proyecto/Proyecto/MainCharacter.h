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

	const char* NAME = "pj";

	bool canJump = true;

public:

	MainCharacter(physx::PxPhysics* gPhysics, physx::PxScene* gScene, Vector3 pos = {0, 0, 0}) : gPhysics(gPhysics), gScene(gScene), 
			pj(gPhysics->createRigidDynamic(physx::PxTransform(pos))), dead_(false) { physx::PxShape* s = Particle::createShape(Particle::Sphere, { 5, 5, 5 });
	pj->attachShape(*s); physx::PxRigidBodyExt::updateMassAndInertia(*pj, 1); rn = new RenderItem(s, pj, { 0, 1, 0, 1 }); gScene->addActor(*pj); pj->setName(NAME); };

	virtual ~MainCharacter() { if (rn != nullptr) delete rn; };


	//-------------------------------------------SETS----------------------------------

	void setColor(Vector4 col) { rn->color = col; };

	inline void setNewJumpForce(float j) { JUMP_FORCE = j; };

	inline void setDead(bool d) { dead_ = d; };

	inline void setCanJump(bool b) { canJump = b; };

	//-------------------------------------------GETS----------------------------------

	inline physx::PxRigidDynamic* getPj() const { return pj; };

	inline float getJumpForce() { return JUMP_FORCE; };

	inline bool isDead() const { return dead_; };

	inline const char* const getPjName() { return NAME; };

	inline bool canThisJump() const { return canJump; };

};

