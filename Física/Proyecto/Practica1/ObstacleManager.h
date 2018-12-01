#pragma once
#include "RigidSystem_Manager.h"
#include <queue>
#include "MainCharacter.h"

class ObstacleManager :
	public RigidSystem_Manager
{
private:
	std::queue<physx::PxRigidStatic*> obstaculos;
	const unsigned int MAX_OBS = 15;
	physx::PxPhysics* gPhysics;
	physx::PxScene* gScene;

	physx::PxRigidStatic* floor;
	int dis_between_obs = 150;
	void generateObstacle();
	void reparteObstaculos();
	void generateFloor();
	void checkFloor();
	void checkObstacle();

public:
	ObstacleManager();

	ObstacleManager(MainCharacter* ch, Particle::Shape shp, physx::PxPhysics* gPhysics, 
		physx::PxScene* gScene) : RigidSystem_Manager(shp, 0, gPhysics, gScene, ch) { for (size_t i = 0; i < MAX_OBS; i++) { generateObstacle(); } 
			reparteObstaculos(); this->setOn(false); generateFloor(); };

	virtual ~ObstacleManager();

	virtual void update(float t);
};

