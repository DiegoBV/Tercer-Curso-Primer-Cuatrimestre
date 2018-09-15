#include "Particle.h"

void Particle::changeDamping(const float newDamping)
{
	if (newDamping >= 0 && newDamping <= 1) //comprobacion de si la nueva fuerza tiene un valor correcto
		damping = newDamping;
	//else ---> avisar, lanzar una excepcion...?	
}

void Particle::integrate(float t)
{
	//Si la masa es infinita, la particula no cambia su posicion (paredes, suelos)
	if (inverse_mass <= 0.0f) return;

	//update de la posicion
	p += v * t;

	//update de la velocidad
	v += a * t;

	//aplicamos la fuerza de rozamiento --> v = v * d^t
	v *= powf(damping, t);
}

void Particle::changeInverseMass(const float newMass)
{
	inverse_mass = newMass;
}
