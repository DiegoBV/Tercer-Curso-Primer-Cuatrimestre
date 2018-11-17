#pragma once
#include "System_Manager.h"
#include "PxRigidDynamic.h"
#include "Particle.h"

class RigidSystem_Manager :
	public System_Manager
{
private:
	const unsigned int MAX_ELEM_;
	physx::PxPhysics* gPhysics = nullptr;
	physx::PxScene* gScene;
	int total_ = 0;
	vector<RenderItem*> rn_items;

protected:
	virtual void generateNewElement(double t);

public:
	RigidSystem_Manager() : System_Manager(), MAX_ELEM_(0) {};

	RigidSystem_Manager(Particle::Shape shp, float t, physx::PxPhysics* gPhysics, physx::PxScene* gScene, int velMax = 50, int velMin = 20, float maxLife = 3, Vector3 pos = { 10, 30, 0 }, int maxElem = 50) :
		System_Manager(shp, t, velMax, velMin, maxLife, pos), gPhysics(gPhysics), gScene(gScene), MAX_ELEM_(maxElem) {};

	virtual ~RigidSystem_Manager() { for (RenderItem* rn : rn_items) { delete rn; rn = nullptr; }; };

	virtual void update(double t);
};

