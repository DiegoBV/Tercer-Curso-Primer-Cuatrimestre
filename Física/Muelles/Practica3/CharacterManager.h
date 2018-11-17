#pragma once
#include "Manager.h"
#include "MainCharacter.h"

class CharacterManager :
	public Manager
{
private:
	MainCharacter* chr;
	float velocity_;

public:
	CharacterManager(float vel) : Manager(), velocity_(vel) {};
	virtual ~CharacterManager() { delete chr; };
	virtual void update(double t);
	virtual void handle_event(unsigned char key);
	void initCharacter() { chr = new MainCharacter(100); register_particle_in_generators(chr); 
		chr->setPosition({ 6, 20, 0 }); chr->setColor({ 0.5, 0, 0.5, 1 }); chr->setActive(); } //llamar despues de anyadir todos los generadores
	MainCharacter* getCharacter() const { return chr; };
};

