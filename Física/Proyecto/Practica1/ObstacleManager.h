#pragma once
#include "RigidSystem_Manager.h"
#include <queue>
#include "MainCharacter.h"

class ObstacleManager :
	public RigidSystem_Manager
{
private:
	struct Obstacle 
	{
		physx::PxRigidStatic* obstacle;
		int type;
		Obstacle(physx::PxRigidStatic* obstacle, int type = 0) : obstacle(obstacle), type(type) {};
		Obstacle() {};
	};

	struct SpecialObstacle: public Obstacle
	{
		physx::PxRigidStatic* pared;
		physx::PxRigidStatic* suelo;
		SpecialObstacle(physx::PxRigidStatic* pared, physx::PxRigidStatic* suelo): Obstacle(pared, 1), suelo(suelo) {};
		SpecialObstacle() {};
	};

	std::queue<Obstacle> obstaculos;
	const unsigned int MAX_OBS = 15;
	physx::PxPhysics* gPhysics;
	physx::PxScene* gScene;
	SpecialObstacle sp;
	const Particle::Medidas ELASTIC_BED_SIZE = { 50, 1, 40 };
	const int IN_JUMP_FORCE;

	physx::PxRigidStatic* floor;
	int dis_between_obs = 100;
	void generateObstacle();
	void reparteObstaculos();
	void generateFloor();
	void checkFloor();
	void checkObstacle();
	void checkElasticBed();
	void generateSpecialObstacle(); //un obstaculo alto con una especie de cama elastica
	void generateObstacleMountain(a); //montanya de objetos dinamicos (puede que con un par valga...) para romper con una granada

public:
	ObstacleManager();

	ObstacleManager(MainCharacter* ch, Particle::Shape shp, physx::PxPhysics* gPhysics, 
		physx::PxScene* gScene) : RigidSystem_Manager(shp, 0, gPhysics, gScene, ch), IN_JUMP_FORCE(ch->getJumpForce()) { for (size_t i = 0; i < MAX_OBS; i++) { generateObstacle(); } 
			generateSpecialObstacle(); reparteObstaculos(); this->setOn(false); generateFloor(); };

	virtual ~ObstacleManager();

	virtual void update(float t);
};

