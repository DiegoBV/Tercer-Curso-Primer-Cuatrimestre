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
	//-------------------------------------------TIPOS DE OBSTACULOS----------------------------------
	struct Obstacle 
	{
		physx::PxRigidStatic* obstacle;
		RenderItem* rn;
		Vector3 initialPosition;
		int type;
		Obstacle(physx::PxRigidStatic* obstacle, RenderItem* rn = nullptr, int type = 0) : obstacle(obstacle), rn(rn), type(type), 
			initialPosition(obstacle->getGlobalPose().p) {};
		Obstacle() {};

		virtual void reset() { obstacle->setGlobalPose(physx::PxTransform(initialPosition)); };
	};

	struct SpecialObstacle: public Obstacle
	{
		physx::PxRigidStatic* pared;
		physx::PxRigidStatic* suelo;
		Vector3 suelo_inPos;
		RenderItem* rn_suelo;
		SpecialObstacle(physx::PxRigidStatic* pared, physx::PxRigidStatic* suelo, RenderItem* rn, RenderItem* rn_suelo): Obstacle(pared, rn, 1), 
			suelo(suelo), rn_suelo(rn_suelo), suelo_inPos(suelo->getGlobalPose().p) {};
		SpecialObstacle() {};

		virtual void reset() { Obstacle::reset(); suelo->setGlobalPose(physx::PxTransform(suelo_inPos)); };
	};

	struct DynamicObstacle : public Obstacle
	{
		physx::PxRigidDynamic* capsula;
		RenderItem* rn_;
		DynamicObstacle(physx::PxRigidDynamic* c, RenderItem* rn, physx::PxRigidStatic* obstacle, RenderItem* rn_ = nullptr) : 
			Obstacle(obstacle, rn_, 2), capsula(c), rn_(rn) { initialPosition = capsula->getGlobalPose().p; };
		DynamicObstacle() {};

		virtual void reset() { capsula->setGlobalPose(physx::PxTransform(initialPosition)); };
	};

	struct WindWall : public Obstacle
	{
		Wind* w = nullptr;
		Vector3 wind_inPos;
		WindWall(Wind* w, physx::PxRigidStatic* o, RenderItem* rn = nullptr) : Obstacle(o, rn, 3), w(w), wind_inPos(w->getCenter()) {};
		WindWall() {};

		virtual void reset() { Obstacle::reset(); w->setCenter(wind_inPos); };
	};

	std::queue<Obstacle> obstaculos;            //cola de obstaculos (ordenados segun distancia, hubiera sido mejor un heap ---> no se puede implementar el operador <)

	const unsigned int MAX_OBS = 30;            //numero de obstaculos que va a haber

	physx::PxPhysics* gPhysics;

	physx::PxScene* gScene;

	SpecialObstacle sp;

	DynamicObstacle do_;

	WindWall ww;

	const Particle::Medidas ELASTIC_BED_SIZE = { 50, 1, 150 };

	Time_GeneratorManager* feedback;                //para la wind wall

	const int IN_JUMP_FORCE;

	const float TIME_TO_RAISE_DIFFICULTY = 60;

	float actual_time_ = 0;

	physx::PxRigidStatic* floor;

	Vector3 floor_inPos;

	int dis_between_obs = 150;  //150 es la mejor, 300 para probarlo/ensenyarlo y que vaya subiendo la dificultad

	//-------------------------------------------METODOS AUXILIARES----------------------------------

	void generateObstacle();

	void reparteObstaculos();

	void generateFloor();

	void raiseDifficulty(float t);

	void checkFloor();

	void checkObstacle();

	void checkElasticBed();

	void checkFeedback();

	void generateSpecialObstacle(); //un obstaculo alto con una especie de cama elastica

	void generateDynamicObstacle(); //un objeto dinamico para romper con una granada

	void generateWindWall(); //pared alta con viento hacia arriba (ultimo obstaculo)

public:
	ObstacleManager();

	ObstacleManager(MainCharacter* ch, Particle::Shape shp, physx::PxPhysics* gPhysics, 
		physx::PxScene* gScene, Time_GeneratorManager* feedback) : RigidSystem_Manager(shp, 0, gPhysics, gScene, ch), 
			IN_JUMP_FORCE(ch->getJumpForce()), feedback(feedback) { this->setOn(false); generateFloor(); };

	virtual ~ObstacleManager();

	virtual void update(float t);

	void initObstacles() { for (size_t i = 0; i < MAX_OBS; i++) { generateObstacle(); } generateSpecialObstacle(); generateDynamicObstacle(); 
		generateWindWall(); reparteObstaculos(); };

	//-------------------------------------------GETS----------------------------------

	inline Wind* getWind() const { return ww.w; };

	inline physx::PxRigidStatic* getFloor() const { return floor; };
};

