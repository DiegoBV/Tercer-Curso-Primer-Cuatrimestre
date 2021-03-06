#include "Particula.h"
#include <iostream>

physx::PxShape* Particula::createShape(Shape tipo, Medidas size)
{
	physx::PxShape* shape_;

	switch (tipo)
	{
	case Capsule:
		shape_ = CreateShape(physx::PxCapsuleGeometry(size.x_, size.y_));
		break;
	case Sphere:
		shape_ = CreateShape(physx::PxSphereGeometry(size.x_));
		break;
	case Box:
		shape_ = CreateShape(physx::PxBoxGeometry(size.x_, size.y_, size.z_));
		break;
	default:
		break;
	}

	return shape_;
}

void Particula::integrate(float t)
{
	//Si la masa es infinita, la particula no cambia su posicion (paredes, suelos)
	if (inverse_mass <= 0.0f) return;

	//update de la posicion (e = e + v*t)
	p += v * t;

	//update de la velocidad
	v += a * t;

	//aplicamos la fuerza de rozamiento --> v = v * d^t
	v *= powf(damping, t);
}