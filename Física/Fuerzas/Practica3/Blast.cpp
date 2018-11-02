#include "Blast.h"

//A VER, MI IDEA ES QUE EN EL MAIN TENGA UNA LISTA (GUAY PARA BORRAR9) DE TOODAS LAS ParticleS QUE SE VAN A RENDERIZAR, EN CADA MANAGER, CADA VEZ QUE SE CREA UNA 
//SE AÑADE ESA A LA LISTA, SI SE BORRA PUES SE BORRA DE DICHA LISTA. EN EL MAIN, SI LE DAS AL ESPACIO...

//OTRA IDEA, PASARLE UNA REFERENCIA A LOS MANAGERS DE UN VECTOR DE EXPLOSIONES (A NULLPTR). AL AÑADIRLOS PUES HACER LA COMPROBACION DE SI NO ES NULLPTR Y TAL
//AL DARLE A LA TECLA QUE SEA, EN EL MAIN, O CREAR UN NUEVO BLAST O SOLAMENTE USAR UN BOOLEANO PARA ACTIVARLO (NO ES MALA IDEA, PARA EMPEZAR SOLAMENTE HACER UN NEW())
//COMO ES UN PUNTERO POR REFERENCIA, SI LE CAMBIO EL VALOR, EN EL UPDATE DE LOS MANAGERS, COMPROBAR SI ES != NULLPTR O SI ESTA ACTIVO ENTONCES HAGO EL REGISTRY.ADD(...)

//LA SEGUNDA IDEA ES LA MEJOR

bool Blast::is_inside(Particle * particle)
{
	Vector3 pos = particle->getPosition();
	return (((center.x + rad) >= (pos.x) && (center.y + rad) >= (pos.y) && (center.z + rad) >= (pos.z)))
		&& ((center.x - rad) <= (pos.x) && (center.y - rad) <= (pos.y) && (center.z - rad) <= (pos.z));
}

bool Blast::is_near(Particle * particle) //----> esto ta mal
{
	Vector3 pos = particle->getPosition();
	return (((center.x + rad/2) >= (pos.x) && (center.y + rad/2) >= (pos.y) && (center.z + rad/2) >= (pos.z)))
		&& ((center.x - rad/2) <= (pos.x) && (center.y - rad/2) <= (pos.y) && (center.z - rad/2) <= (pos.z));
}

bool Blast::is_medium_distance(Particle * particle)
{
	Vector3 pos = particle->getPosition();
	return (((center.x + rad / 4) >= (pos.x) && (center.y + rad / 4) >= (pos.y) && (center.z + rad / 4) >= (pos.z)))
		&& ((center.x - rad / 4) <= (pos.x) && (center.y - rad / 4) <= (pos.y) && (center.z - rad / 4) <= (pos.z));
}

void Blast::deactivate()
{
	if (auxRef >= references_) {  //si ya ha comprobado todas las Particles que tiene referenciadas, la explosion se desactiva
		active_ = false;
		auxRef = 0;
	}
}

Blast::Blast()
{
}


Blast::~Blast()
{
	delete rn;
}

void Blast::updateForce(Particle * particle, float t)
{
	if (is_inside(particle)) {
		Vector3 dir = particle->getPosition() - center;
		dir.normalize();

		if (is_near(particle)) {
			particle->addForce(dir *force * 5 * particle->getMass());
		}
		else if (is_medium_distance(particle)) {
			particle->addForce(dir *force * particle->getMass());
		}
		else {
			particle->addForce(dir *force / 5 * particle->getMass());
		}
	}

	auxRef++;

	deactivate();
}
