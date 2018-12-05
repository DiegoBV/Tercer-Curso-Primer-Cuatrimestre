#pragma once
#include "RigidSystem_Manager.h"
#include <queue>
#include "MainCharacter.h"
#include "Time_GeneratorManager.h"
#include "Wind.h"

class ObstacleManager :
	public RigidSystem_Manager
{
private:
	struct Obstacle 
	{
		physx::PxRigidStatic* obstacle;
		RenderItem* rn;
		int type;
		Obstacle(physx::PxRigidStatic* obstacle, RenderItem* rn = nullptr, int type = 0) : obstacle(obstacle), rn(rn), type(type) {};
		Obstacle() {};
	};

	struct SpecialObstacle: public Obstacle
	{
		physx::PxRigidStatic* pared;
		physx::PxRigidStatic* suelo;
		RenderItem* rn_suelo;
		SpecialObstacle(physx::PxRigidStatic* pared, physx::PxRigidStatic* suelo, RenderItem* rn, RenderItem* rn_suelo): Obstacle(pared, rn, 1), 
			suelo(suelo), rn_suelo(rn_suelo) {};
		SpecialObstacle() {};
	};

	struct DynamicObstacle : public Obstacle
	{
		physx::PxRigidDynamic* capsula;
		RenderItem* rn_;
		DynamicObstacle(physx::PxRigidDynamic* c, RenderItem* rn, physx::PxRigidStatic* obstacle, RenderItem* rn_ = nullptr) : 
			Obstacle(obstacle, rn_, 2), capsula(c), rn_(rn) {};
		DynamicObstacle() {};
	};

	struct WindWall : public Obstacle
	{
		Wind* w = nullptr;
		WindWall(Wind* w, physx::PxRigidStatic* o, RenderItem* rn = nullptr) : Obstacle(o, rn, 3), w(w) {};
		WindWall() {};
	};

	std::queue<Obstacle> obstaculos;
	const unsigned int MAX_OBS = 30;
	physx::PxPhysics* gPhysics;
	physx::PxScene* gScene;
	SpecialObstacle sp;
	DynamicObstacle do_;
	WindWall ww;
	const Particle::Medidas ELASTIC_BED_SIZE = { 50, 1, 150 };
	Time_GeneratorManager* feedback;
	const int IN_JUMP_FORCE;

	physx::PxRigidStatic* floor;
	int dis_between_obs = 200;
	void generateObstacle();
	void reparteObstaculos();
	void generateFloor();
	void checkFloor();
	void checkObstacle();
	void checkElasticBed();
	void checkFeedback();
	void generateSpecialObstacle(); //un obstaculo alto con una especie de cama elastica
	void generateDynamicObstacle(); //un objeto dinamico para romper con una granada
	void generateWindWall(); //pared alta con viento hacia arriba (ultimo obstaculo) -->DESPUES DE ESTO, VER COMO EL JUGADOR PIERDE Y VUELVE AL PRINCIPIO...

public:
	ObstacleManager();

	ObstacleManager(MainCharacter* ch, Particle::Shape shp, physx::PxPhysics* gPhysics, 
		physx::PxScene* gScene, Time_GeneratorManager* feedback) : RigidSystem_Manager(shp, 0, gPhysics, gScene, ch), 
			IN_JUMP_FORCE(ch->getJumpForce()), feedback(feedback) { this->setOn(false); generateFloor(); };

	virtual ~ObstacleManager();

	virtual void update(float t);

	void initObstacles() { for (size_t i = 0; i < MAX_OBS; i++) { generateObstacle(); } generateSpecialObstacle(); generateDynamicObstacle(); 
		generateWindWall(); reparteObstaculos(); };

	inline Wind* getWind() const { return ww.w; };
};

