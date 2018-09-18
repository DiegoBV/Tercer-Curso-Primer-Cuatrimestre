#pragma once
#include "Vector3.h"
class Particle
{
private:
	//fuerza de rozamiento
	float damping;
	//masa inversa
	float inverse_mass;

public:
	//Posicion en el mundo
	Vector3 p;
	//Velocidad (lineal) en el mundo
	Vector3 v;
	//Aceleracion (lineal) en el mundo
	Vector3 a;

	//constructor por defecto
	Particle(): damping(0.999) {};
	//constructor explicito---> necesario?
	Particle(const Vector3 position, const Vector3 velocity, const Vector3 acceleration) : p(position), v(velocity), a(acceleration), inverse_mass(100) {
		p = position;
	}
	//destructora por defecto
	virtual ~Particle() {};
	//cambiar fuerza de rozamiento
	void changeDamping(const float newDamping);
	//Integracion
	void integrate(float t);
	//cambiar masa
	void changeInverseMass(const float newMass);
};

