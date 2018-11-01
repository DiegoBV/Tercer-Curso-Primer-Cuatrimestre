#include "Particula.h"
#include "ParticleForceRegistry.h"
#include <iostream>

ParticleForceRegistry Particula::registry_ = ParticleForceRegistry();

void Particula::clearForce()
{
	force.x = force.y = force.z = 0;
}

void Particula::addForce(const Vector3 & f)
{
	force += f;
}

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
	if (inverse_mass <= 0.0f) return;                   //Si la masa es infinita, la particula no cambia su posicion (paredes, suelos)

	p += v * t;                                         //update de la posicion (e = e + v*t)

	Vector3 totalAcceleration = a;                      //forces
	a += force * inverse_mass;
	
	v += a * t;                                        //update de la velocidad

	v *= powf(damping, t);                            //aplicamos la fuerza de rozamiento --> v = v * d^t

	transform.p = p;

	clearForce();
}