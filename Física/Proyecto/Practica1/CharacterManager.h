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

public:
	CharacterManager(float vel, physx::PxPhysics* gPhysics, physx::PxScene* gScene, Vector3 pos = { 0, 0, 0 }) : Manager(), velocity_(vel), 
		gPhysics(gPhysics), gScene(gScene), initial_pos(pos) {};

	virtual ~CharacterManager() { delete chr; };

	virtual void update(float t);

	virtual void handle_event(unsigned char key);

	void initCharacter() { chr = new MainCharacter(100, gPhysics, gScene, initial_pos); register_rigid_body_in_generators(chr->getPj()); 
	chr->setColor({ 0.5, 0, 0.5, 1 }); chr->getPj()->setLinearVelocity({ 0, 0, -velocity_ }); } //llamar despues de anyadir todos los generadores

	inline MainCharacter* getCharacter() const { return chr; };
};

