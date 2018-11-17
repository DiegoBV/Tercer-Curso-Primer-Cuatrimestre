#pragma once
#include "Particle.h"
class MainCharacter :
	public Particle
{
private:
	int life_;

public:
	MainCharacter() : Particle() {};
	virtual ~MainCharacter() {};
	MainCharacter(int life) : life_(life), Particle(new RenderItem()) { setBoxShape(5, 5, 5); };
	void stopMovement() { setAcceleration({ 0, 0, 0 }); setVelocity({ 0, 0, 0 }); };
};

