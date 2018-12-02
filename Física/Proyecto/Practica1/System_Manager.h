#pragma once
#include "Manager.h"
class System_Manager :
	public Manager
{
private:
	bool on = true;

protected:
	//------------------------------------------------PARAMETERS------------------------------------------------
	Particle::Shape shape_;
	float time_inter = 0;
	float next_period = 0;
	float tiempo_transcurrido = 0;
	Vector3 pos;
	const int VEL_MAX_;
	const int VEL_MIN_;
	const float MAX_LIFE_TIME_;

	//------------------------------------------------AUX METHODS------------------------------------------------
	Vector3 generateRandomVel();
	virtual void generateNewElement(double t) = 0;

public:
	System_Manager(): VEL_MAX_(0), VEL_MIN_(0), MAX_LIFE_TIME_(0) {};

	System_Manager(Particle::Shape shp, float t, int velMax = 50, int velMin = 20, float maxLife = 3, Vector3 pos = { 10, 30, 0 }, MainCharacter* ch = nullptr) : Manager(ch),
		shape_(shp), time_inter(t), VEL_MAX_(velMax), VEL_MIN_(velMin), MAX_LIFE_TIME_(maxLife), pos(pos) {};

	virtual ~System_Manager() {};

	virtual void handle_event(unsigned char key);

	virtual void update(float t) = 0;

	void setOn(bool on) { this->on = on; };

	bool isOn() const { return on; };
};

