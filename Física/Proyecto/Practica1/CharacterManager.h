#pragma once
#include "Manager.h"
#include "MainCharacter.h"

class CharacterManager :
	public Manager
{
private:

	MainCharacter* chr;

	float velocity_;

	physx::PxPhysics* gPhysics = nullptr; 

	physx::PxScene* gScene = nullptr;

	Vector3 initial_pos;

	float time_passed_ = 0;

	int death_count = 0;

	const float DIST_TO_CAMERA_ = -70;

	const float DIST_TO_CHECK_ = -150;        //dist to check if char is dead

	const float DELAY_ = 3;                   //delay entre muerte y respawn

	void checkIfPJisDead();


public:

	CharacterManager(float vel, physx::PxPhysics* gPhysics, physx::PxScene* gScene, Vector3 pos = { 0, 0, 0 }) : Manager(), velocity_(vel), 
		gPhysics(gPhysics), gScene(gScene), initial_pos(pos) {};

	virtual ~CharacterManager() { delete chr; };

	//-------------------------------------------AUXILIARES----------------------------------

	virtual void update(float t);

	virtual void handle_event(unsigned char key);

	//resucita al personaje
	void resCharacter(float t);

	//init del personaje
	void initCharacter() { chr = new MainCharacter(gPhysics, gScene, initial_pos); chr->setColor({ 0.5, 0, 0.5, 1 }); chr->getPj()->setLinearVelocity({ 0, 0, -velocity_ }); } //llamar despues de anyadir todos los generadores
	
	//-------------------------------------------GETS----------------------------------

	inline MainCharacter* getCharacter() const { return chr; };

	inline int getDeathCount() const { return death_count; };
};

