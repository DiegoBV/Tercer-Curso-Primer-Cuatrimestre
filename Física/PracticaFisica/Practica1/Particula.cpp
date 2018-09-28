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

void Particula::changeDamping(const float newDamping)
{
	if (newDamping >= 0 && newDamping <= 1) //comprobacion de si la nueva fuerza tiene un valor correcto
		damping = newDamping;
	//else ---> avisar, lanzar una excepcion...?	
}

void Particula::changeInverseMass(const float newMass)
{
	inverse_mass = newMass;
}
